#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if defined(PSTADE_OVEN_TEST_EXTENSION_NO_ORDER_DEPENDENCY)
    #include <boost/range.hpp>
    #include <pstade/oven/extension.hpp>
#else
    #include <pstade/oven/extension.hpp>
    #include <boost/range.hpp>
#endif

#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <vector>
#include <boost/utility/enable_if.hpp> // enable_if
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/size.hpp>




namespace mine {

    struct container1
    {
        typedef std::vector<int> impl_t;
        impl_t m_impl;
    };

    template< class A, class B >
    struct container2 : private boost::noncopyable
    {
        typedef std::vector<A> impl_t;
        impl_t m_impl;
    };

        template< class T >
        struct is_container2 : boost::mpl::false_ { };

        template< class A, class B >
        struct is_container2< container2<A, B> > : boost::mpl::true_ { };


    namespace inside {

        struct container3
        {
            typedef std::vector<char> impl_t;
            impl_t m_impl;
        };

    }

    template< class T >
    struct is_container :
        boost::mpl::or_<
            boost::is_same<T, container1>,
            is_container2<T>,
            boost::is_same<T, inside::container3>
        >
    { };

}


struct your_sequence :
    private boost::noncopyable
{
    std::string m_str;
};



namespace pstade_oven_extension {

    template< class T >
    struct Range_base<T,
        typename enable_if< mine::is_container<T> >::type >
    {
        template< class X >
        struct associate
        {
            typedef typename X::impl_t::iterator mutable_iterator;
            typedef typename X::impl_t::const_iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.m_impl.begin();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.m_impl.end();
        }
    };

    template< >
    struct Range< ::your_sequence >
    {
        template< class X >
        struct associate
        {
            typedef std::string::iterator mutable_iterator;
            typedef std::string::const_iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.m_str.begin();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.m_str.end();
        }
    };

}


PSTADE_OVEN_EXTENSION_OF_TYPE((mine)(container1))
PSTADE_OVEN_EXTENSION_OF_TEMPLATE((mine)(container2), 2)
PSTADE_OVEN_EXTENSION_OF_TYPE((mine)(inside)(container3))

PSTADE_OVEN_EXTENSION_OF_TYPE((your_sequence))


namespace Foo {

    template< class T >
    struct Pair
    {
        T first, last;
    };

} // namespace Foo

namespace pstade_oven_extension {

    template< class T >
    struct Range< Foo::Pair<T> >
    {
        // X == Foo::Pair<T>
        template< class X >
        struct associate
        {
            typedef T mutable_iterator;
            typedef T constant_iterator;
        };

        // if X is not const, Iterator == mutable_iterator;
        // otherwise, Iterator == constant_iterator.
        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.first;
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.last;
        }

        // optional, but recommanded.
        template< class X, class From >
        X copy(From& rng)
        {
            X x;
            x.first = boost::begin(rng);
            x.last  = boost::end(rng);
            return x;
        }
    };

} // namespace pstade_oven_extension

PSTADE_OVEN_EXTENSION_OF_TEMPLATE((Foo)(Pair), (class))
// PSTADE_OVEN_EXTENSION_OF_TEMPLATE((Foo)(Pair), 1) // also ok.


void pstade_minimal_test()
{
    using namespace pstade;

    mine::container1 cont1;
    std::vector<int> expected_int;
    mine::container2<int, char> cont2;
    mine::inside::container3 cont3;
    std::vector<char> expected_char;
    ::your_sequence seq1;
    Foo::Pair<int *> pr;

    bool never = false;
    if (never) {
        oven::test::random_access_constant(cont1, expected_int);
        oven::test::random_access_constant(cont2, expected_int);
        oven::test::random_access_constant(cont3, expected_char);
        oven::test::random_access_constant(seq1,  expected_char);
        oven::test::random_access_constant(pr,    expected_int);
        oven::test::copyable< Foo::Pair<int *> >(pr);

        boost::size(cont1);
        boost::size(cont2);
        boost::size(seq1);
        boost::size(pr);
    }
}
