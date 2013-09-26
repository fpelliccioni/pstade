#ifndef PSTADE_EGG_LESS_EQUAL_HPP
#define PSTADE_EGG_LESS_EQUAL_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/binary_pred.hpp"


namespace pstade { namespace egg {

    #define  PSTADE_EGG_BINARY_PRED_PARAMS (less_equal, <=)
    #include PSTADE_EGG_BINARY_PRED()

} }


#endif
