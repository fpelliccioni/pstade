#ifndef PSTADE_OVEN_REVERSED_HPP
#define PSTADE_OVEN_REVERSED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Eric Niebler, reverse_range, Boost.RangeEx, 2004.
//     http://www.boost-consulting.com/vault/index.php?directory=Algorithms


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./reverse_iterator.hpp"


namespace pstade { namespace oven {


namespace reversed_detail {


    template< class Range >
    struct base
    {
        typedef
            reverse_iterator<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
            return result_type(boost::end(rng), boost::begin(rng)); // take care of the order!
        }
    };


} // namespace reversed_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(reversed, (reversed_detail::base<_>))


} } // namespace pstade::oven


#endif
