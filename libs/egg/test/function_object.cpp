

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


struct T_foo
{
    typedef int& result_type;

    int& operator()(int& i) const
    {
        i += 1;
        return i;
    }
};

PSTADE_POD_CONSTANT((T_foo), foo) = { };

int main()
{
    int i = 10;
    void const * volatile p = &(foo(i));
}
