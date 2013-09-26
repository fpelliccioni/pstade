#ifndef PSTADE_KETCHUP_CMD_UI_IMPL_CHILDWINDOW_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_IMPL_CHILDWINDOW_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/check_window.hpp>
#include <pstade/gravy/enable_window.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/set_window_text.hpp>
#include <pstade/gravy/window_ref.hpp>
#include "../cmd_ui.hpp"


namespace pstade { namespace ketchup {


struct childwindow_cmd_ui : cmd_ui
{
    childwindow_cmd_ui(UINT uID, gravy::window_ref child) :
        cmd_ui(uID), m_child(child)
    { }

private:
    void override_enable(bool on)
    {
        gravy::enable_window(m_child, on);
    }

    void override_set_check(int state)
    {
        // we can only check buttons or controls acting like buttons
        gravy::check_window(m_child, state);
    }

    void override_set_text(TCHAR const *pszText)
    {
        gravy::set_window_text(m_child, pszText);
    }

private:
    gravy::window_ref m_child;
};


} } // namespace pstade::ketchup


#endif
