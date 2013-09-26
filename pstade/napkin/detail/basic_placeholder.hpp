#ifndef PSTADE_NAPKIN_DETAIL_BASIC_PLACEHOLDER_HPP
#define PSTADE_NAPKIN_DETAIL_BASIC_PLACEHOLDER_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/any.hpp>
//
// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string> // basic_string
#include <typeinfo>
#include <pstade/egg/copy.hpp>
#include <pstade/egg/lexicalize.hpp>


namespace pstade { namespace napkin { namespace detail {


template< class CharT >
struct basic_placeholder
{
    virtual ~basic_placeholder()
    { } // In fact, shared_ptr emulates 'virtual'.

    std::type_info const& typeid_() const
    {
        return override_typeid();
    }

    template< class OutputStreamable >
    void output(const OutputStreamable& x)
    {
        override_output(
            egg::copy< std::basic_string<CharT> >(x|egg::lexicalize()).c_str()
        );
    }

protected:
    virtual std::type_info const& override_typeid() const = 0;
    virtual void override_output(const CharT *psz) = 0;
};


} } } // namespace pstade::napkin::detail


#endif
