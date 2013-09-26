#ifndef PSTADE_OVEN_APPLIED_HPP
#define PSTADE_OVEN_APPLIED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Will be cute with the upcoming Boost.Phoenix2.


#include "./concepts.hpp"
#include "./detail/little_to_adaptor.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace applied_detail {


    struct little
    {
        template< class Myself, class Range, class, class = void >
        struct apply
        {
            typedef typename
                iter_range_of<Range>::type const
            type;
        };

        template< class Result, class Range, class Begin, class End >
        Result call(Range& rng, Begin& b, End& e) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return Result(b(rng), e(rng));
        }

        template< class Result, class Range, class Make >
        Result call(Range& rng, Make& make) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return Result(make(rng));
        }
    };


} // namespace applied_detail


PSTADE_OVEN_LITTLE_TO_ADAPTOR(applied, (applied_detail::little))


} } // namespace pstade::oven


// for Boost.Phoenix2
//
#if defined(PSTADE_OVEN_USING_PHOENIX_V2)

    #include <boost/spirit/phoenix/core/argument.hpp>
    #include <pstade/constant.hpp>

    namespace pstade { namespace oven {

    PSTADE_CONSTANT(rng1, (boost::phoenix::actor< boost::phoenix::argument<0> >))

    } } // namespace pstade::oven

#endif


#endif
