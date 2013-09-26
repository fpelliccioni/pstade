#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/memoize.hpp>
#include <pstade/unit_test.hpp>


#include <boost/progress.hpp>
#include <iostream>


namespace egg = pstade::egg;
using namespace egg;


struct fib_block
{
    typedef int result_type;

    template<class Fixed>
    int operator()(Fixed f, int x) const
    {
        return x <= 1 ? 1 : f(x-1) + f(x-2);
    }

    template<class Fixed>
    int operator()(Fixed f, std::string) const
    {
        return 1;
    }
};


void pstade_unit_test()
{
    {
        BOOST_CHECK(memoize(fib_block())(10) == 89);
    }
    {
        pstade::result_of<T_memoize(fib_block)>::type mfib = memoize(fib_block());
        BOOST_CHECK( mfib(10) == 89);

        bool thrown = false;
        try {
            mfib(std::string("bad"));
        }
        catch (boost::bad_any_cast) {
            thrown = true;
        }
        BOOST_CHECK(thrown);
    }
    {
        boost::progress_timer t;
        BOOST_CHECK(memoize(fib_block())(30) == 1346269);
    }
    {
        boost::progress_timer t;
        BOOST_CHECK(fix(curry2(fib_block()))(30) == 1346269);
    }
}
