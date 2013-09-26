#ifndef PSTADE_HAMBURGER_RECTANGLE_HPP
#define PSTADE_HAMBURGER_RECTANGLE_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/wtl/misc.hpp> // CRect


namespace pstade { namespace hamburger {


    typedef WTL::CRect
    rectangle;


    inline
    rectangle swap_axis(rectangle const& rc)
    {
        return hamburger::rectangle(rc.top, rc.left, rc.bottom, rc.right);
    }


} } // namespace pstade::hamburger


#endif
