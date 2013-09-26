#ifndef PSTADE_OVEN_RANGE_MUTABLE_ITERATOR_HPP
#define PSTADE_OVEN_RANGE_MUTABLE_ITERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include "./detail/config.hpp"

#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    #include <boost/range/iterator.hpp>
#else
    #include <boost/range/mutable_iterator.hpp>
#endif


namespace pstade { namespace oven {


template< class Range >
struct range_mutable_iterator :
#if defined(PSTADE_OVEN_BOOST_RANGE_VERSION_1)
    boost::range_iterator<
#else
    boost::range_mutable_iterator<
#endif
        typename boost::remove_cv<Range>::type
    >
{ };


} } // namespace pstade::oven


#endif
