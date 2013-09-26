#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_NO_ACTIONS_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_NO_ACTIONS_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "../../state/actionable_guard.hpp"


namespace pstade { namespace biscuit {


template< class Parser >
struct no_actions
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        state_actionable_guard<State> sa(s, false);
        return Parser::parse(s, us);
    }
};


} } // namespace pstade::biscuit


#endif
