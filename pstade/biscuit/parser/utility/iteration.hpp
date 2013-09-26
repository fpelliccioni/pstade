#ifndef PSTADE_BISCUIT_PARSER_UTILITY_ITERATION_HPP
#define PSTADE_BISCUIT_PARSER_UTILITY_ITERATION_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Thanks to:
//
// ITOU-T15


#include <boost/range/empty.hpp>
#include "../../action/null_action.hpp"
#include "../../config/nullary_parser.hpp"
#include "../actor.hpp"
#include "../any.hpp"
#include "../directive/no_actions.hpp"
#include "../directive/no_captures.hpp"
#include "../end.hpp"
#include "../orn.hpp"
#include "../seqn.hpp"
#include "../star.hpp"
#include "../star_before.hpp"


namespace pstade { namespace biscuit {


namespace iteration_detail {


    template< class GapAction >
    struct if_not_empty
    {
        template< class SubRange, class UserState >
        void operator()(SubRange& rng, UserState& us) const
        {
            if (boost::empty(rng))
                return;

            GapAction()(rng, us);
        }
    };


} // namespace iteration_detail


template<
    class Parser,
    class GapAction = null_action
>
struct iteration :
    seq2<
        star<
            or_2<
                Parser,
                actor<
                    star_before<
                        PSTADE_BISCUIT_NULLARY_PARSER(any),
                        no_captures< no_actions<Parser> > 
                    >,
                    GapAction
                >
            >
        >,
        actor<
            star_before<
                PSTADE_BISCUIT_NULLARY_PARSER(any),
                PSTADE_BISCUIT_NULLARY_PARSER(end)
            >,
            iteration_detail::if_not_empty<GapAction>
        >
    >
{ };


} } // namespace pstade::biscuit


#endif
