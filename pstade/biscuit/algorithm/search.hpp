#ifndef PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP
#define PSTADE_BISCUIT_ALGORITHM_SEARCH_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/make_function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/range_iterator.hpp>
#include "../state/increment.hpp"
#include "../state/is_end.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"
#include "./detail/without_results.hpp"


namespace pstade { namespace biscuit {


namespace search_detail {


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
            typedef typename oven::range_iterator<state_t>::type iter_t;

            state_t s(r, rs);
            for (; !biscuit::state_is_end(s); biscuit::state_increment(s)) {
                iter_t const marker = s.get_cur();
                if (Parser::parse(s, us))
                    return oven::make_iter_range(marker, s.get_cur());
            }

            BOOST_ASSERT( boost::end(s) == boost::end(r) );
            return Result(boost::end(s), boost::end(s));
        }

        template< class Result, class ParsingRange, class MatchResults >
        Result call(ParsingRange& r, MatchResults& rs) const
        {
            return egg::make_function(*this)(r, rs, null_state);
        }
    };


} // namespace search_detail


template< class Parser >
struct X_results_search :
    egg::function< search_detail::little<Parser> >
{ };

#define  PSTADE_EGG_SPECIFIED_PARAMS (results_search, X_results_search, (class), (2)(3))
#include PSTADE_EGG_SPECIFIED()


template< class Parser >
struct X_search :
    detail::X_without_results<X_results_search, Parser>
{ };

#define  PSTADE_EGG_SPECIFIED_PARAMS (search, X_search, (class), (1)(2))
#include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::biscuit


#endif
