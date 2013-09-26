#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/affect.hpp>
#include <boost/test/minimal.hpp>


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int const volatile&, double>::type,
    double const volatile&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int const volatile, double>::type,
    double const volatile
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int const, double>::type,
    double const
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int volatile, double>::type,
    double volatile
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int, double>::type,
    double
> ));


// no affects

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int const volatile&, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int const volatile, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int const, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int volatile, double&>::type,
    double&
> ));

BOOST_MPL_ASSERT(( boost::is_same<
    pstade::affect<int, double&>::type,
    double&
> ));


void test()
{
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
