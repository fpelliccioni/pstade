#ifndef PSTADE_BISCUIT_PARSER_OPT_HPP
#define PSTADE_BISCUIT_PARSER_OPT_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace biscuit {


template< class Parser >
struct opt
{
    template< class State, class UserState >
    static bool parse(State& s, UserState& us)
    {
        Parser::parse(s, us);
        return true;
    }
};


} } // namespace pstade::biscuit


#endif
