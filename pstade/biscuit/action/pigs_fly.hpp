#ifndef PSTADE_BISCUIT_ACTION_PIGS_FLY_HPP
#define PSTADE_BISCUIT_ACTION_PIGS_FLY_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>


namespace pstade { namespace biscuit {


struct pigs_fly
{
    template< class ParsingSubRange, class UserState >
    void operator()(ParsingSubRange&, UserState&) const
    {
        BOOST_ASSERT(false && "when pigs fly");
    }
};


} } // namespace pstade::biscuit


#endif
