#ifndef PSTADE_PAUSE_HPP
#define PSTADE_PAUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream> // cin
#include <pstade/pod_constant.hpp>


namespace pstade {


    struct T_pause
    {
        typedef int result_type;

        int operator()() const
        {
            std::cin.ignore();
            // or std::cin.get();

            return 0; // for 'main'
        }
    };


    PSTADE_POD_CONSTANT((T_pause), pause) = {};


} // namespace pstade


#endif
