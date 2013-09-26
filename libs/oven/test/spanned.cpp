#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/spanned.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include "./detail/v1_core.hpp"
#include <pstade/oven/elements.hpp>
#include <pstade/oven/spanned.hpp>


bool is_even(int x)
{
    return x % 2 == 0;
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int rng[] = {0,2,4,8,6,10,3,5,2,5,6,1};
        int ans0[] = {0,2,4,8,6,10};
        int ans1[] = {3,5,2,5,6,1};
        std::vector<int> expected0 = ans0|copied;
        std::vector<int> expected1 = ans1|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|spanned(&::is_even)|elements_c<0>(),
            expected0
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|spanned(&::is_even)|elements_c<1>(),
            expected1
        ) );
    }
    {

    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
