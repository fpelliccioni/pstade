#ifndef PSTADE_TOMATO_ADD_REBAR_BAND_HPP
#define PSTADE_TOMATO_ADD_REBAR_BAND_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/assert.hpp>
#include <boost/range/empty.hpp>
#include <pstade/candy/set.hpp>
#include <pstade/gravy/c_str.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/size_initialize.hpp>
#include <pstade/gravy/window_ref.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/begin_end.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/jointed.hpp>
#include <pstade/oven/pointed.hpp>
#include <pstade/oven/single.hpp>
#include <pstade/require.hpp>
#include "./get_rebar_band_info.hpp"
#include "./wtl/ctrls.hpp" // CReBarCtrl


namespace pstade { namespace tomato {


    template< class CStringizable > // 'cx' can be 0.
    void add_rebar_band(gravy::window_ref rebar, gravy::window_ref child, UINT fStyle, CStringizable const& str, UINT cx)
    {
        BOOST_ASSERT("child window id must be valid." && ::GetDlgCtrlID(child) != 0);


        // info.lpText is not 'const'. 'const_cast' is dangerous,
        // so that, copy it.
        std::vector<TCHAR> text; {
            text = str|gravy::c_str|oven::as_c_str
                |oven::jointed(oven::single(_T('\0')))|oven::copied;
            BOOST_ASSERT(oven::contains_zero(text));
        }

        bool hasTitle = !boost::empty(text|oven::as_c_str);


        REBARBANDINFO info; {
            info|gravy::size_initialize();

    #if (_WIN32_IE >= 0x0400)
            info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE | RBBIM_IDEALSIZE;
    #else
            info.fMask = RBBIM_CHILD | RBBIM_CHILDSIZE | RBBIM_STYLE | RBBIM_ID | RBBIM_SIZE;
    #endif
            
            if (hasTitle)
                candy::set(info.fMask, RBBIM_TEXT);
            
            info.fStyle = fStyle;
            info.lpText = text|oven::pointed|oven::begin;
            info.hwndChild = child;
            info.wID = ::GetDlgCtrlID(child); // how's that

            info.cxMinChild = tomato::get_rebar_band_info_cxMinChild(child, hasTitle);
            info.cyMinChild = tomato::get_rebar_band_info_cyMinChild(child);
            
            // cx is the "current" width.
            if (cx == 0)
                info.cx = tomato::get_rebar_band_info_cxIdeal(child);
            else
                info.cx = cx;

    #if (_WIN32_IE >= 0x0400)
            // Note: cxIdeal is used for CHEVRON. If MDI, cxIdeal is changed dynamically.
            info.cxIdeal = tomato::get_rebar_band_info_cxIdeal(child); // info.cx is not good.
    #endif
        } // info


        PSTADE_REQUIRE(WTL::CReBarCtrl(rebar).InsertBand(-1, &info));


    /* should be?
    #if (_WIN32_IE >= 0x0501)
            DWORD dwExStyle = (DWORD)::SendMessage(child, TB_GETEXTENDEDSTYLE, 0, 0L);
            ::SendMessage(child, TB_SETEXTENDEDSTYLE, 0, dwExStyle | TBSTYLE_EX_HIDECLIPPEDBUTTONS);
    #endif // (_WIN32_IE >= 0x0501)
    */

    }


} } // namespace pstade::tomato


#endif
