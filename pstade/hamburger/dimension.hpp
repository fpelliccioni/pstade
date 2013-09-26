#ifndef PSTADE_HAMBURGER_DIMENSION_HPP
#define PSTADE_HAMBURGER_DIMENSION_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/wtl/misc.hpp> // CSize


namespace pstade { namespace hamburger {


    typedef WTL::CSize
    dimension;


    inline
    dimension swap_axis(dimension const& sz)
    {
        return hamburger::dimension(sz.cy, sz.cx);
    }


} } // namespace pstade::hamburger


#endif
