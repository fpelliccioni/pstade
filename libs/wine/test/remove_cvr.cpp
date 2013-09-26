#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/remove_cvr.hpp>
#include <boost/test/minimal.hpp>


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int const>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int volatile>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int const volatile>::type > ));

BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int const&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int volatile&>::type > ));
BOOST_MPL_ASSERT(( boost::is_same< int, pstade::remove_cvr<int const volatile&>::type > ));


int test_main(int, char*[])
{
    return 0;
}
