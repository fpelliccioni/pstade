#ifndef PSTADE_OVEN_IO_HPP
#define PSTADE_OVEN_IO_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright (C) 2001 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//               2001 Gary Powell (gary.powell@sierra.com)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
// For more information, see http://www.boost.org 


// References:
//
// [1] <boost/tuple/tuple_io.hpp>
// [2] <boost/fusion/include/io.hpp>


#include <locale> // isspace
#include <iosfwd>
#include <boost/assert.hpp>
#include <boost/implicit_cast.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/pod_constant.hpp>
#include "./iter_range.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace io_detail {


    namespace here = io_detail;


    enum mn_t
    {
        mn_open, mn_close, mn_delimiter, mn_SIZE
    };


    inline
    int mn_id(int mn)
    {
        static int const index[mn_SIZE] = {
            std::ios::xalloc(), std::ios::xalloc(), std::ios::xalloc()
        };

        return index[mn];
    }


    template< class Stream, class CharT >
    void set_mn_char(Stream& s, mn_t mn, CharT ch)
    {
        s.iword(mn_id(mn)) = static_cast<long>(ch);
    }

    template< class Stream >
    typename Stream::char_type get_mn_char(Stream& s, mn_t mn)
    {
        typedef typename Stream::char_type char_t;
        char_t ch = static_cast<char_t>( s.iword(mn_id(mn)) );

        if (ch)
            return ch;

        // defaults
        switch (mn) {
            case mn_open:
                ch = s.widen('{');
                break;
            case mn_close: 
                ch = s.widen('}');
                break;
            case mn_delimiter:
                ch = s.widen(',');
                break;
            default:
                BOOST_ASSERT(false);
                break;
        }

        return ch;
    }

    template< class IStream >
    void eat_mn_char(IStream& is, mn_t mn)
    {
        typename IStream::char_type const ch = here::get_mn_char(is, mn);

        if (std::isspace(ch, is.getloc()))
            return;

        if (is.get() != ch) {
            is.unget();
            is.setstate(std::ios::failbit);
        }
    }


    template< class IStream, class Iterator >
    void in(IStream& is, Iterator first, Iterator last)
    {
        bool is_beginning = true;
        for (; first != last; ++first) {
            if (!is_beginning)
                here::eat_mn_char(is, mn_delimiter);
            else
                is_beginning = false;

            if (!is.good())
                break;

            is >> read(first);
        }
    }


    template< class OStream, class Iterator >
    void out(OStream& os, Iterator first, Iterator last)
    {
        typename OStream::char_type const delim = here::get_mn_char(os, mn_delimiter);

        bool is_beginning = true;
        for (; first != last; ++first) {
            if (!is_beginning)
                os << delim;
            else
                is_beginning = false;

            os << read(first);
        }
    }


    template< class CharT >    
    struct manipulator
    {
        manipulator(mn_t mn, CharT ch) :
            m_mn(mn), m_ch(ch)
        { }

        mn_t const m_mn;
        CharT const m_ch;

    private:
        manipulator& operator=(manipulator const&);
    };

    template< class CharT, class Traits > inline
    std::basic_istream<CharT, Traits>&
    operator>>(std::basic_istream<CharT, Traits>& is, manipulator<CharT> m) 
    {
        here::set_mn_char(is, m.m_mn, m.m_ch);
        return is;
    }

    template< class CharT, class Traits > inline
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, manipulator<CharT> m)
    {
        here::set_mn_char(os, m.m_mn, m.m_ch);
        return os;
    }


#define PSTADE_base_manipulator(Name) \
    template< class CharT > \
    struct BOOST_PP_CAT(base_, Name) \
    { \
        typedef \
            manipulator< \
                typename boost::remove_cv<CharT>::type \
            > const \
        result_type; \
        \
        result_type operator()(CharT& ch) const \
        { \
            return result_type(BOOST_PP_CAT(mn_, Name), ch); \
        } \
    }; \
/**/

    PSTADE_base_manipulator(open)
    PSTADE_base_manipulator(close)
    PSTADE_base_manipulator(delimiter)

#undef  PSTADE_base_manipulator


} // namespace io_detail


template< class Iterator, class Injector, class CharT, class Traits >
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is, iter_range<Iterator, Injector> const& rng)
{
    if (!is.good())
        return is;

    io_detail::eat_mn_char(is, io_detail::mn_open);
    io_detail::in(is, boost::begin(rng), boost::end(rng));
    io_detail::eat_mn_char(is, io_detail::mn_close);

    return is;
}


template< class Iterator, class Injector, class CharT, class Traits >
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, iter_range<Iterator, Injector> const& rng)
{
    CharT const l = io_detail::get_mn_char(os, io_detail::mn_open);
    CharT const r = io_detail::get_mn_char(os, io_detail::mn_close);

    os << l;   
    io_detail::out(os, boost::begin(rng), boost::end(rng));
    os << r;

    return os;
}


typedef PSTADE_EGG_DEFER((io_detail::base_open<boost::mpl::_>)) T_range_open;
PSTADE_POD_CONSTANT((T_range_open), range_open) = PSTADE_EGG_DEFERRED;

typedef PSTADE_EGG_DEFER((io_detail::base_close<boost::mpl::_>)) T_range_close;
PSTADE_POD_CONSTANT((T_range_close), range_close) = PSTADE_EGG_DEFERRED;

typedef PSTADE_EGG_DEFER((io_detail::base_delimiter<boost::mpl::_>)) T_range_delimiter;
PSTADE_POD_CONSTANT((T_range_delimiter), range_delimiter) = PSTADE_EGG_DEFERRED;


} } // namespace pstade::oven


#endif
