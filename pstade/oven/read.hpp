#ifndef PSTADE_OVEN_READ_HPP
#define PSTADE_OVEN_READ_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A dereference of ReadableIterator returns a type "convertible" to
// associated 'value_type', but it is useless for writing generic code.
//
// Once 'read' is applied to non-Lvalue one, the result is not Assignable,
// meaning that the iterator loses Writability.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/is_reference_iterator.hpp"


namespace pstade { namespace oven {


template< class ReadableOrLvalueIter >
struct iterator_read :
    boost::mpl::eval_if< detail::is_reference_iterator<ReadableOrLvalueIter>,
        boost::iterator_reference<ReadableOrLvalueIter>,
        boost::iterator_value<ReadableOrLvalueIter>
    >
{ };


namespace read_detail {


    template< class ReadableOrLvalueIter >
    struct base
    {
        typedef typename
            iterator_read<
                typename boost::remove_cv<ReadableOrLvalueIter>::type
            >::type
        result_type;

        // Pass by reference; see "./reverse_iterator.hpp"
        result_type operator()(ReadableOrLvalueIter& it) const
        {
            return *it;
        }
    };


} // namespace read_detail


typedef PSTADE_EGG_DEFER((read_detail::base<boost::mpl::_>)) T_read;
PSTADE_POD_CONSTANT((T_read), read) = PSTADE_EGG_DEFERRED;


} } // namespace pstade::oven


#endif
