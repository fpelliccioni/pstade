#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/result_of.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/bll/config.hpp>
#include <pstade/egg/bll/placeholders.hpp>
#include <pstade/egg/bll/bind.hpp>
#include <pstade/egg/plus.hpp>
#include <pstade/egg/identity.hpp>
#include <pstade/test.hpp>


namespace bll = boost::lambda;
using namespace pstade::egg;
using pstade::result_of;


PSTADE_TEST_IS_RESULT_OF((int&), T_bll_1(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const&))
#if defined(PSTADE_EGG_BLL_PERFECT_FUNCTORS)
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int))
    PSTADE_TEST_IS_RESULT_OF((int const&), T_bll_1(int const))
#endif


void pstade_minimal_test()
{

    {
        int i = 10;
        result_of<T_bll_1(int&)>::type r = bll_1(i);
        BOOST_CHECK(&r == &i);
        BOOST_CHECK(r == 10);
    }
    {
        int const i = 10;
        result_of<T_bll_1(int const&)>::type r = bll_1(i);
        BOOST_CHECK(&r == &i);
        BOOST_CHECK(r == 10);
    }

#if defined(PSTADE_EGG_BLL_PERFECT_FUNCTORS)
    {
        result_of<T_bll_1(int)>::type r = bll_1(10);
        BOOST_CHECK(r == 10);
    }
#endif

    {
        typedef result_of<T_bll_bind(T_plus const&, int, T_bll_1 const&)>::type fun_t;
        fun_t fun = bll_bind(plus, 3, bll_1);

        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int&))
        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int const&))

#if defined(PSTADE_EGG_BLL_PERFECT_FUNCTORS)
        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int))
        PSTADE_TEST_IS_RESULT_OF((int), fun_t(int const))
#endif

        int i = 9;
        BOOST_CHECK( fun(i) == 3+9 );
#if defined(PSTADE_EGG_BLL_PERFECT_FUNCTORS)
        BOOST_CHECK( fun(9) == 3+9 );
#endif
    }

    {
        typedef result_of<T_bll_bind(T_identity const&, T_bll_1 const&)>::type fun_t;
        fun_t fun = bll_bind(identity, bll_1);

        PSTADE_TEST_IS_RESULT_OF((int&), fun_t(int&))
        PSTADE_TEST_IS_RESULT_OF((int const&), fun_t(int const&))

#if defined(PSTADE_EGG_BLL_PERFECT_FUNCTORS)
        PSTADE_TEST_IS_RESULT_OF((int const&), fun_t(int))
        PSTADE_TEST_IS_RESULT_OF((int const&), fun_t(int const))
#endif

        int i = 9;
        BOOST_CHECK( fun(i) == 9 );
#if defined(PSTADE_EGG_BLL_PERFECT_FUNCTORS)
        BOOST_CHECK( fun(9) == 9 );
#endif
    }

}
