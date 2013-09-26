#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/compose.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/egg/to_value.hpp>


std::string g_str("x");


struct bar_fun
{
    typedef std::string result_type;

    std::string operator()(char) const
    {
        return "x";
    }
};


// nullary check
int make_zero()
{
    return 0;
}

int increment(int i)
{
    return i + 1;
}


struct A { };
struct B { };
A get_A() { return A(); }
B get_B() { return B(); }


using namespace pstade::egg;

/*
BOOST_MPL_ASSERT((
    boost::is_same<
        std::string,
        pstade::result_of<
            pstade::result_of<
                T_compose(T_value const, bar_fun)
            >::type
            (char)
        >::type
    >
));
*/


template<class F>
void nullary_result_of_check(F f)
{
    BOOST_MPL_ASSERT((boost::is_same<
        typename pstade::result_of<F()>::type,
        int
    >));
}



void pstade_minimal_test()
{
    {
        BOOST_CHECK( compose(pstade::egg::to_value, ::bar_fun())('c') == std::string("x") );
    }
    {
        // make_zero is known to be nullary and composable to increment.
        BOOST_CHECK( X_compose<use_nullary_result>()(&::increment, &::make_zero)() == 1 );
        ::nullary_result_of_check( X_compose<use_nullary_result>()(&::increment, &::make_zero) );
    }
    {
        // specify nullary result type explicity.
        BOOST_CHECK( X_compose<int>()(&::increment, &::make_zero)() == 1 );
        ::nullary_result_of_check( X_compose<int>()(&::increment, &::make_zero) );
    }
    {
        // well-formed even if non-composable.
        compose(&::get_A, &::get_B);
        X_compose<int>()(&::get_A, &::get_B);
    }
}
