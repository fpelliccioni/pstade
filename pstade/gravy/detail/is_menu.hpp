#ifndef PSTADE_GRAVY_DETAIL_IS_MENU_HPP
#define PSTADE_GRAVY_DETAIL_IS_MENU_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/debug.hpp>
#include <pstade/pod_constant.hpp>
#include "../booleanize.hpp"
#include "../sdk/windows.hpp"


namespace pstade { namespace gravy { namespace detail {


    struct T_is_menu
    {
        typedef bool result_type;

        bool operator()(HMENU hMenu) const
        {
            debugging();
            return ::IsMenu(hMenu)|booleanize();
        }
    };


    PSTADE_POD_CONSTANT((T_is_menu), is_menu) = {};


} } } // namespace pstade::gravy::detail


#endif
