#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/curry.hpp>
#include <pstade/egg/uncurry.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/minimal_test.hpp>


using namespace pstade::egg;


//[code_curried_plus
int plus(int x, int y)
{
    return x + y;
}

typedef result_of_curry2<int (*)(int, int)>::type T_curried_plus;
T_curried_plus const curried_plus = PSTADE_EGG_CURRY2(&::plus);

void test()
{
    BOOST_CHECK( curry2(&::plus)(4)(9) == 13 );
    BOOST_CHECK( curried_plus(4)(9) == plus(4, 9) );
    BOOST_CHECK( uncurry(curry2(plus))(4, 9) == 13 );
}
//]


void pstade_minimal_test()
{
    test();
}
