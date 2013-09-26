#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_MENU_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_MENU_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/gravy/get_menu_item_count.hpp>
#include <pstade/gravy/get_menu_item_id.hpp>
#include <pstade/gravy/menu_ref.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/window_ref.hpp>
#include "../impl/menu_cmd_ui.hpp"
#include "./cmd_ui.hpp"


namespace pstade { namespace ketchup {


namespace cmd_ui_detail {


    inline
    bool is_possibly_popup_menu_id(UINT uID)
    {
        return uID == static_cast<UINT>(-1);
    }


    inline
    bool is_separator_or_invalid_id(UINT uID)
    {
        return uID == 0;
    }


} // namespace cmd_ui_detail


inline
void update_menu_cmd_ui(gravy::window_ref updater, gravy::menu_ref menu)
{
    // See:
    // MFC7::CFrameWnd::OnInitMenuPopup

    for (int i = 0, count = gravy::get_menu_item_count(menu); i < count; ++i)
    {
        UINT uID = gravy::get_menu_item_id(menu, i);
        if (cmd_ui_detail::is_separator_or_invalid_id(uID))
            continue;

        if (cmd_ui_detail::is_possibly_popup_menu_id(uID))
        {
            // route to first item of that popup
            HMENU hSubMenu = ::GetSubMenu(menu, i);
            if (
                hSubMenu == NULL ||
                cmd_ui_detail::is_separator_or_invalid_id(uID = gravy::get_menu_item_id(hSubMenu, 0)) ||
                cmd_ui_detail::is_possibly_popup_menu_id(uID)
            )
            {
                continue; // first item of popup can't be routed to
            }

            // popup menu item
            menu_cmd_ui ui(uID, menu, i, true);
            ketchup::update_cmd_ui(updater, ui);
        }
        else
        {
            // normal menu item
            menu_cmd_ui ui(uID, menu, i, false);
            ketchup::update_cmd_ui(updater, ui);
        }

        // adjust for menu deletions and additions
        int new_count = gravy::get_menu_item_count(menu);
        if (new_count < count)
        {
            i -= (count - new_count);
            while (i < new_count && gravy::get_menu_item_id(menu, i) == uID)
                ++i;
        }
        count = new_count;
    } // for
}


} } // namespace pstade::ketchup


#endif
