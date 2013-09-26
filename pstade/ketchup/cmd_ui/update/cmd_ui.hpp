#ifndef PSTADE_KETCHUP_CMD_UI_UPDATE_CMD_UI_HPP
#define PSTADE_KETCHUP_CMD_UI_UPDATE_CMD_UI_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/gravy/send_message.hpp>
#include <pstade/gravy/window_ref.hpp>
#include "../update_cmd_ui_message.hpp"


namespace pstade { namespace ketchup {


inline
bool update_cmd_ui(gravy::window_ref updater, cmd_ui& ui)
{
    LRESULT lResult = gravy::send_message(updater,
        ketchup::id_update_cmd_ui_message(), ketchup::cmd_ui_to_wParam(ui));

    return ketchup::is_cmd_ui_handled(lResult);
}


} } // namespace pstade::ketchup


#endif
