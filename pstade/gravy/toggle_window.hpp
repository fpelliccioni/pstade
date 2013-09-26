#ifndef PSTADE_GRAVY_TOGGLE_WINDOW_HPP
#define PSTADE_GRAVY_TOGGLE_WINDOW_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./booleanize.hpp"
#include "./sdk/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    struct T_toggle_window
    {
        typedef bool result_type;

        bool operator()(window_ref wnd) const
        {
            BOOL bVisible = !::IsWindowVisible(wnd);
            ::ShowWindow(wnd, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);

            return bVisible|booleanize();
        }
    };


    PSTADE_POD_CONSTANT((T_toggle_window), toggle_window) = {};


} } // namespace pstade::gravy


#endif
