#ifndef PSTADE_OVEN_WIDE_CHARS_HPP
#define PSTADE_OVEN_WIDE_CHARS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include <pstade/egg/make_function.hpp>
#include <pstade/result_of.hpp>
#include "./detail/little_to_adaptor.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace wide_chars_detail {


    template< class CharT >
    struct to_widen
    {
        typedef CharT result_type;

        CharT operator()(char ch) const
        {
            return std::use_facet< std::ctype<CharT> >(m_loc).widen(ch);
        }

        explicit to_widen()
        { }

        explicit to_widen(std::locale const& loc) :
            m_loc(loc)
        { }

    private:
        std::locale m_loc;
    };


    template< class CharT >
    struct little
    {
        template< class Myself, class Range, class Locale = void >
        struct apply :
            result_of<
                T_make_transformed(Range&, wide_chars_detail::to_widen<CharT>)
            >
        { };

        template< class Result, class Range > inline
        Result call(Range& rng, std::locale const& loc) const
        {
            return make_transformed(rng, wide_chars_detail::to_widen<CharT>(loc));
        }

        template< class Result, class Range > inline
        Result call(Range& rng) const
        {
            return egg::make_function(*this)(rng, std::locale());
        }
    };


} // namespace wide_chars_detail


template< class CharT = wchar_t >
struct X_make_wide_chars :
    egg::function< wide_chars_detail::little<CharT> >
{ };


PSTADE_OVEN_LITTLE_TO_ADAPTOR(wide_chars, (X_make_wide_chars<>::little_type))


} } // namespace pstade::oven



#endif
