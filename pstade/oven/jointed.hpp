#ifndef PSTADE_OVEN_JOINTED_HPP
#define PSTADE_OVEN_JOINTED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/joint_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace jointed_detail {


    template< class RangeL, class RangeR >
    struct base
    {
        typedef
            detail::joint_iterator<
                typename range_iterator<RangeL>::type,
                typename range_iterator<RangeR>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(RangeL& rngL, RangeR& rngR) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<RangeL>));
            PSTADE_CONCEPT_ASSERT((SinglePass<RangeR>));
            return aux(boost::begin(rngL), boost::end(rngL), boost::begin(rngR), boost::end(rngR));
        }

        template< class IteratorL, class IteratorR >
        result_type aux(IteratorL firstL, IteratorL lastL, IteratorR firstR, IteratorR lastR) const
        {
            return result_type(iter_t(firstL, lastL, firstR, firstR), iter_t(lastL, lastL, firstR, lastR));
        }
    };


} // namespace jointed_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(jointed, (jointed_detail::base<_, _>))


} } // namespace pstade::oven


#endif
