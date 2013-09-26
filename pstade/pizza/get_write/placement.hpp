#ifndef PSTADE_PIZZA_GET_WRITE_PLACEMENT_HPP
#define PSTADE_PIZZA_GET_WRITE_PLACEMENT_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(_WIN32_WCE)


#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/size_initialize.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/require.hpp>
#include "./window_placement.hpp"


namespace pstade { namespace pizza {


template< class Profile >
void write_placement(Profile& pr, gravy::window_ref wnd)
{
    WINDOWPLACEMENT wndpl;
    gravy::size_initialize(wndpl);
    PSTADE_REQUIRE(::GetWindowPlacement(wnd, &wndpl));

    pizza::write_window_placement(pr, wndpl);
}


template< class Profile >
void get_placement(Profile& pr, gravy::window_ref wnd)
{
    WINDOWPLACEMENT wndpl = pizza::get_window_placement(pr);
    PSTADE_REQUIRE(::SetWindowPlacement(wnd, &wndpl));
}


} } // namespace pstade::pizza


#endif // !defined(_WIN32_WCE)


#endif
