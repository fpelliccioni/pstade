#ifndef PSTADE_OVEN_TAKEN_HPP
#define PSTADE_OVEN_TAKEN_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This adaptor might return:
//   base          -> adapted
//   RandomAccess  -> RandomAccess
//   Bidirectional -> Forward
//   Forward       -> Forward
//   SinglePass    -> SinglePass
// But "Bidirectional -> Forward" seems inconsistent.


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/take_while_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace taken_detail {


    template< class Difference >
    struct countdown
    {
        template< class Iterator >
        bool operator()(Iterator)
        {
            return m_n--
                != 0; // suppress a VC++ warning.
        }

        explicit countdown()
        { }

        explicit countdown(Difference n) :
            m_n(n)
        { }

    private:
        Difference m_n;
    };


    template< class Range >
    struct base
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef
            detail::take_while_iterator<
                typename range_iterator<Range>::type,
                countdown<diff_t>
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, diff_t n) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            BOOST_ASSERT(0 <= n);
            return aux(boost::begin(rng), boost::end(rng), countdown<diff_t>(n));
        }

        template< class Iterator >
        result_type aux(Iterator first, Iterator last, countdown<diff_t> cd) const
        {
            return result_type(iter_t(first, last, cd), iter_t(last, last, cd));
        }
    };


} // namespace taken_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(taken, (taken_detail::base<_>))


} } // namespace pstade::oven


#endif
