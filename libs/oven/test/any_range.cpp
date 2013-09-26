#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/any_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/egg/do_swap.hpp>


#include <pstade/unit_test.hpp>
#include "./detail/test.hpp"
#include <boost/static_assert.hpp>
#include <pstade/oven/stream_read.hpp>
#include <iostream>


namespace oven = pstade::oven;
using namespace oven;


void test_iterator()
{

    std::string src("abc");
    {
        any_iterator<char&, boost::forward_traversal_tag, char, std::ptrdiff_t> it1(boost::begin(src));
        BOOST_CHECK( it1.contains<std::string::iterator>() );
        BOOST_CHECK( !it1.contains<std::string::const_iterator>() );
        std::string::iterator b = it1.content<std::string::iterator>();
        BOOST_CHECK( b == boost::begin(src) );
        any_iterator<char const&, boost::single_pass_traversal_tag, char, std::ptrdiff_t> it2 = it1; // copy-initialization, but type-erased
        BOOST_CHECK( it2 == it1 );
        it2 = it1;
        BOOST_CHECK( it2 == it1 );
    }
    {
        any_iterator<char&, boost::random_access_traversal_tag, char> it1(boost::begin(src));
        any_iterator<char&, boost::random_access_traversal_tag, char> it2 = it1; // copy-initialization, just a copy.
        BOOST_CHECK( it2 == it1 );
        BOOST_CHECK( (it2 - it1) == 0 );
        it2 = it1;
        BOOST_CHECK( it2 == it1 );
    }
    {
        any_iterator<char&, boost::random_access_traversal_tag, char, std::ptrdiff_t> it1(boost::begin(src));
        any_iterator<char const&, boost::random_access_traversal_tag, char, int> it2 = it1; // copy-initialization, but type-erased
        BOOST_CHECK( it2 == it1 );
        BOOST_CHECK( (it2 - it1) == 0 );
        it2 = it1;
        BOOST_CHECK( it2 == it1 );
    }
    {
        any_iterator<char&, boost::forward_traversal_tag, char, std::ptrdiff_t> it1;
        it1 = boost::begin(src);
        std::string::iterator b = it1.content<std::string::iterator>();
        BOOST_CHECK( b == boost::begin(src) );
    }
    {
        any_iterator<char&, boost::single_pass_traversal_tag, char, std::ptrdiff_t> it1;
        it1 = boost::begin(src);
        std::string::iterator b = it1.content<std::string::iterator>();
        BOOST_CHECK( b == boost::begin(src) );
    }
}

void test_type()
{
    std::string src("abc");
    {
        any_iterator<char&, boost::forward_traversal_tag, char, std::ptrdiff_t> it1;
        BOOST_CHECK(it1.empty());
        BOOST_CHECK(it1.type() == typeid(void));
        BOOST_CHECK(!it1.contains<int *>());
        it1 = boost::begin(src);
        BOOST_CHECK(!it1.empty());
        BOOST_CHECK(it1.type() == typeid(std::string::iterator));
        BOOST_CHECK( it1.contains<std::string::iterator>() );
        BOOST_CHECK( !it1.contains<std::string::const_iterator>() );
    }
}


void test_incrementable()
{
    std::string src("abc");
    {
        any_iterator<char&, boost::incrementable_traversal_tag> it1(boost::begin(src));
        ++it1;
        BOOST_CHECK( &*it1 == &src[1]);
        it1++;
        BOOST_CHECK( &*it1 == &src[2]);

        BOOST_CHECK( it1.contains<std::string::iterator>() );
        BOOST_CHECK( !it1.contains<std::string::const_iterator>() );

        std::string::iterator b = it1.content<std::string::iterator>();
        BOOST_CHECK( b == boost::begin(src) + 2 );

        any_iterator<char const&, boost::incrementable_traversal_tag, char, std::ptrdiff_t> it2 = it1; // copy-initialization.
        BOOST_CHECK( &*it2 == &src[2] );
    }
}


void test_make()
{
    {
        std::string str("abcdefg");
        pstade::result_of<T_make_any_range(std::string&)>::type
            r = make_any_range(str);

        BOOST_CHECK( oven::equals(str, r) );
    }
}


void test_swap()
{
    {
        std::string s1("abdefg");
        std::string s2("hijlkm");

        any_iterator<char &, boost::random_access_traversal_tag> a1(s2.begin());
        any_iterator<char &, boost::random_access_traversal_tag> a2(s1.begin());
        pstade::egg::do_swap(a1, a2);
        BOOST_CHECK( s1.begin() == a1.content<std::string::iterator>() );
        BOOST_CHECK( s2.begin() == a2.content<std::string::iterator>() );
    }
    {
        std::string s1("abdefg");
        std::string s2("hijlkm");
        any_range<char &, boost::random_access_traversal_tag> rng1(s2);
        any_range<char &, boost::random_access_traversal_tag> rng2(s1);
        pstade::egg::do_swap(rng1, rng2);
        BOOST_CHECK( equals(rng1, s1) );
        BOOST_CHECK( equals(rng2, s2) );

        BOOST_CHECK( rng1 );
        rng1 = boost::none;
        BOOST_CHECK( rng1.iter_empty() );
        std::type_info const & info = rng2.iter_type();
        (void)info;
    }
}


void test_none()
{
    {
        std::string s("abdefg");
        any_iterator<char &, boost::random_access_traversal_tag> a = boost::none;
        BOOST_CHECK( a.empty() );
        a = s.begin();
        BOOST_CHECK(!a.empty() );
        a.reset(boost::none);
        BOOST_CHECK( a.empty() );
        a = s.begin();
        BOOST_CHECK(!a.empty() );
        a = boost::none;
        BOOST_CHECK( a.empty() );
        a = s.begin();
        BOOST_CHECK(!a.empty() );
    }
    {
        std::string s("abdefg");
        any_range<char &, boost::random_access_traversal_tag> a = boost::none;
        BOOST_CHECK( a.iter_empty() );
        a = s;
        BOOST_CHECK(!a.iter_empty() );
        a.reset(boost::none);
        BOOST_CHECK( a.iter_empty() );
        a = s;
        BOOST_CHECK(!a.iter_empty() );
        a = boost::none;
        BOOST_CHECK( a.iter_empty() );
        a = s;
        BOOST_CHECK(!a.iter_empty() );
    }
}


void test_any_to_any()
{
    std::string src("8frj91j81hf891y2");
    any_range<char&, boost::random_access_traversal_tag> a1(src);
    BOOST_CHECK( equals(src, a1) );
    any_range<char&, boost::random_access_traversal_tag> a2;
    a2.reset(pstade::as_type_erasure, a1); // any to any
    BOOST_CHECK(a2.iter_type() == typeid(any_range<char&, boost::random_access_traversal_tag>::iterator));
    BOOST_CHECK( equals(src, a2) );
}


// compile check only.
void test_from_single_pass()
{
    any_range<char, boost::single_pass_traversal_tag> a1 = oven::stream_read<char>(std::cin);
    (void)a1;
}


void pstade_unit_test()
{
    ::test_iterator();

    namespace lambda = boost::lambda;

    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b(a);

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1 is lovely.
        BOOST_STATIC_ASSERT((boost::is_convertible<
            range_traversal< any_range<char&, boost::random_access_traversal_tag> >::type,
            boost::bidirectional_traversal_tag
        >::value));
#endif

        test::random_access_swappable(b, a);
        test::non_lightweight_copyable(b);
        BOOST_CHECK(b); // bool-testable check
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b; // DefaultConstructible
        b = a;
        test::random_access_swappable(b, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b = a|identities; // copy-initializable with 'iter_range'.
        test::random_access_swappable(b, a);
    }
   {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b = a|identities; // copy-initializable with 'iter_range'.
        any_range<char, boost::single_pass_traversal_tag> b2 = b; // copy-initializable with 'any_range'.
        test::single_pass_readable(b2, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::bidirectional_traversal_tag> b(a|identities(boost::bidirectional_traversal_tag()));
        test::bidirectional_swappable(b, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::forward_traversal_tag> b(a|identities(boost::forward_traversal_tag()));
        test::forward_swappable(b, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::single_pass_traversal_tag> b(a|identities(boost::single_pass_traversal_tag()));
        test::single_pass_readable(b, a);
        test::lightweight_copyable(b);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char, boost::single_pass_traversal_tag> b = a|test::proxies;
        test::single_pass_readable(b, a);
        test::lightweight_copyable(b);
    }
    {
        std::string a;
        any_range<char&, boost::random_access_traversal_tag> b(a|identities);
        test::emptiness(b);
        BOOST_CHECK(!b); // bool-testable check
    }
    {
        std::string rng("abcd");
        typedef any_iterator<char&, boost::random_access_traversal_tag, char, std::ptrdiff_t> many_iter;
        many_iter many(boost::begin(rng));
        // many.content<char *>(); // bad_cast!
        many.content<std::string::iterator>();
    }
    {
        std::string str("jgi8e8qnboie");

        // rejected:
        // any_range_of<std::string>::type any_ = str; // copy-initializable
        
        any_range_of<std::string>::type any_(str); // copy-initializable
        BOOST_CHECK( equals(str, any_) );
    }

    ::test_type();
    ::test_incrementable();
    ::test_make();
    ::test_swap();
    ::test_none();
    ::test_any_to_any();
}
