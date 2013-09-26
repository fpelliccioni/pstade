#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/infix.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/to_string.hpp>
#include <pstade/egg/plus.hpp>
#include <string>


struct str_plus_int
{
    typedef std::string result_type;

    result_type operator()(std::string s, int i) const
    {
        return s + pstade::egg::to_string(i);
    }
};


void pstade_minimal_test()
{
    using namespace pstade::egg::infix;
    using pstade::egg::plus;

    {
        std::string l("hello");
        int r = 12;
        BOOST_CHECK( (std::string("hello") ^str_plus_int()^ 12) == "hello12" );
        BOOST_CHECK( (l ^str_plus_int()^ 12) == "hello12" );
        BOOST_CHECK( (std::string("hello") ^str_plus_int()^ r) == "hello12" );
        BOOST_CHECK( (l ^str_plus_int()^ r) == "hello12" );
    }
    {
        int l = 10, r = 12;
        BOOST_CHECK( (10 ^plus^ 12) == 22 );
        BOOST_CHECK( (l ^plus^ 12) == 22 );
        BOOST_CHECK( (10 ^plus^ r) == 22 );
        BOOST_CHECK( (l ^plus^ r) == 22 );
    }
    {
        BOOST_CHECK( (10 ^plus^ 12 ^plus^ 3) == 25 );
    }
}
