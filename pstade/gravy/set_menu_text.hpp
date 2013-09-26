#ifndef PSTADE_GRAVY_SET_MENU_TEXT_HPP
#define PSTADE_GRAVY_SET_MENU_TEXT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/require.hpp>
#include "./c_str.hpp"
#include "./get_menu_state.hpp"
#include "./menu_ref.hpp"
#include "./mf_bitmap.hpp"
#include "./sdk/tchar.hpp"
#include "./sdk/windows.hpp"
#include "./modify_menu.hpp"
#include "./size_initialize.hpp"


namespace pstade { namespace gravy {


    struct T_set_menu_text
    {
        typedef void result_type;

        template<class CStringizable>
        void operator()(menu_ref menu, UINT uIndex, CStringizable const& text) const
        {
            // get current menu_ref state so it doesn't change
            UINT uState = get_menu_state(menu, uIndex, MF_BYPOSITION);
            candy::remove(uState, mf_bitmap::value | MF_OWNERDRAW | MF_SEPARATOR);

            // set menu_ref text
            MENUITEMINFO mii = { 0 }; {
                mii|size_initialize();
                mii.fMask = MIIM_ID;
                PSTADE_REQUIRE(::GetMenuItemInfo(menu, uIndex, TRUE, &mii));
            }

            PSTADE_REQUIRE(modify_menu(menu, uIndex, MF_BYPOSITION |
                MF_STRING | uState, mii.wID, c_str(text))
            );
        }
    };


    PSTADE_POD_CONSTANT((T_set_menu_text), set_menu_text) = {};


} } // namespace pstade::gravy


#endif
