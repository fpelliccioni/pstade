#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_TESTS_DONT_CALL_DISTANCE
#include <pstade/oven/xpressive_tokenized.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <string>
#include <vector>
#include <boost/xpressive/xpressive.hpp>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/concatenated.hpp>
#include <pstade/oven/memoized.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string input("This is his face");
        boost::xpressive::sregex re = +boost::xpressive::_w; // a word

        bool f = false;
        if (f) {
            input|xpressive_tokenized(re);
            input|xpressive_tokenized(re, -1);
            input|xpressive_tokenized(re, std::vector<int>(), boost::xpressive::regex_constants::match_default);
        }

        // oops, concatenated cannot support xpressive_token_iterator and boost::token_iterator.
        // Hence, turn it into Independent using memoized.
        std::vector<char> expected = std::string("Thisishisface")|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            input|xpressive_tokenized(re)|memoized|concatenated,
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
