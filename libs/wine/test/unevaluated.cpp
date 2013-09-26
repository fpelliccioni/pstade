#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/unevaluated.hpp>
#include <pstade/minimal_test.hpp>

struct A {};

using pstade::unevaluated;

void pstade_minimal_test()
{
    bool b = false;
    if (b)
        unevaluated<int>();
    if (b)
        unevaluated<A>();
    if (b)
        unevaluated<A&>();
}
