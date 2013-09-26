#ifndef PSTADE_CANDY_RESET_HPP
#define PSTADE_CANDY_RESET_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include "./count.hpp"
#include "./remove.hpp"


namespace pstade { namespace candy {


template< class Flags, class Flag > inline
Flags& reset(Flags& fs, Flag const& f)
{
    BOOST_ASSERT("multiple flags not allowed" && candy::count(f) == 1);
    return candy::remove(fs, f);
}


template< class Flags > inline
Flags& reset(Flags& flags)
{
    flags = 0;
    return flags;
}


} } // namespace pstade::candy


#endif
