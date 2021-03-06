#ifndef PSTADE_BISCUIT_ALGORITHM_PARSE_HPP
#define PSTADE_BISCUIT_ALGORITHM_PARSE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/oven/iter_range.hpp>
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"
#include "./detail/without_results.hpp"


namespace pstade { namespace biscuit {


namespace parse_detail {


    template< class Parser >
    struct little
    {
        template< class Myself, class ParsingRange, class MatchResults, class UserState = void >
        struct apply
        {
            typedef typename
                oven::iter_range_of<ParsingRange>::type const
            type;
        };

        template< class Result, class ParsingRange, class MatchResults, class UserState >
        Result call(ParsingRange& r, MatchResults& rs, UserState& us) const
        {
            typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;

            state_t s(r, rs);
            Parser::parse(s, us);
            return Result(boost::begin(s), s.get_cur());
        }

        template< class Result, class ParsingRange, class MatchResults >
        Result call(ParsingRange& r, MatchResults& rs) const
        {
            return egg::make_function(*this)(r, rs, null_state);
        }
    };


} // namespace parse_detail


template< class Parser >
struct X_results_parse :
    egg::function< parse_detail::little<Parser> >
{ };

#define  PSTADE_EGG_SPECIFIED_PARAMS (results_parse, X_results_parse, (class), (2)(3))
#include PSTADE_EGG_SPECIFIED()


template< class Parser >
struct X_parse :
    detail::X_without_results<X_results_parse, Parser>
{ };

#define  PSTADE_EGG_SPECIFIED_PARAMS (parse, X_parse, (class), (1)(2))
#include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::biscuit


#endif
