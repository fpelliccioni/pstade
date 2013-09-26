#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/sub_set.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <vector>
#include "./detail/v1_core.hpp"


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string src("abcde");
        std::string::iterator its[] = { boost::begin(src), boost::begin(src)+2, boost::begin(src)+4 };
        oven::sub_set<std::string> ss2(its);
        BOOST_CHECK( oven::equals(ss2, std::string("ace")) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
