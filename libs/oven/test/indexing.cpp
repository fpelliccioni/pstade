#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// For some reason, difference_type for size_t is __int64.
#include <pstade/vodka/drink_loss_of_data.hpp>


#include <pstade/oven/indexing.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/algorithm.hpp>


std::vector<char> g_vec;


struct vec_get
{
    typedef char result_type;

    template< class Size >
    char operator()(Size i) const
    {
        return g_vec[i];
    }
};


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string ans("11111234516313!");
        oven::copy(ans, std::back_inserter(g_vec));

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            oven::indexing(0, ans.size(), vec_get()),
            g_vec
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
