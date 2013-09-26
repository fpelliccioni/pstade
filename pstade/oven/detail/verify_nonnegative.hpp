#ifndef PSTADE_OVEN_DETAIL_VERIFY_NONNEGATIVE_HPP
#define PSTADE_OVEN_DETAIL_VERIFY_NONNEGATIVE_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Difference > inline
Difference verify_nonnegative(Difference n)
{
    BOOST_ASSERT(0 <= n);
    return n;
}


} } } // namespace pstade::oven::detail


#endif
