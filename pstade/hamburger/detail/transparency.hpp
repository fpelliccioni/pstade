#ifndef PSTADE_HAMBURGER_DETAIL_TRANSPARENCY_HPP
#define PSTADE_HAMBURGER_DETAIL_TRANSPARENCY_HPP


#if !(_WIN32_WINNT >= 0x0500)
    #error requires '_WIN32_WINNT >= 0x0500'.
#endif


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.codeproject.com/dialog/smoothalpha.asp


#include <pstade/gravy/rgb.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/atl/win.hpp> // CWindow
#include "./view_attributes.hpp"


namespace pstade { namespace hamburger { namespace detail {


    namespace transparency_detail {


        inline
        void add(gravy::window_ref wnd, COLORREF clr)
        {
            ATL::CWindow(wnd).ModifyStyleEx(0, WS_EX_LAYERED);
            PSTADE_REQUIRE(::SetLayeredWindowAttributes(wnd, clr, 1, LWA_COLORKEY));
        }


        inline
        void remove(gravy::window_ref wnd)
        {
            ATL::CWindow(wnd).ModifyStyleEx(WS_EX_LAYERED, 0);
        }


    } // namespace transparency_detail


    template< class Element >
    void reset_transparency(Element& elem)
    {
        boost::optional<COLORREF> clr = gravy::rgb(elem%Name_transparencyColor);
        if (clr)
            transparency_detail::add(*elem.window(), *clr);
    }


    template< class Element >
    void remove_transparency(Element& elem)
    {
        transparency_detail::remove(*elem.window());
    }


} } } // namespace pstade::hamburger::detail


#endif
