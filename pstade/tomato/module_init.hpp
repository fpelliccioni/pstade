#ifndef PSTADE_TOMATO_MODULE_INIT_HPP
#define PSTADE_TOMATO_MODULE_INIT_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/gravy/sdk/winerror.hpp> // SUCCEEDED
#include <pstade/require.hpp>
#include "./atl/module.hpp"


namespace pstade { namespace tomato {


    namespace module_init_detail {


        inline
        void resolve_thunking_problem()
        {
            // Workaround:
            // This resolves ATL window thunking problem
            // when Microsoft Layer for Unicode (MSLU) is used.
            ::DefWindowProc(NULL, 0, 0, 0L);    
        }


    } // namespace module_init_detail


    struct module_init
    {
        explicit module_init(HINSTANCE hInstance)
        {
            PSTADE_REQUIRE(SUCCEEDED(_Module.Init(NULL, hInstance)));
            module_init_detail::resolve_thunking_problem();
        }

        ~module_init()
        {
            _Module.Term();
        }
    };


} } // namespace pstade::tomato


#endif
