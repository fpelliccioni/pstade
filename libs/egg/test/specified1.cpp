#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/specified.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>


template<class X>
struct T_my_cast
{
    typedef X result_type;

    X operator()(int i) const
    {
        return i;
    }
};

#define  PSTADE_EGG_SPECIFIED_PARAMS (my_cast, T_my_cast, 1, (1))
#include PSTADE_EGG_SPECIFIED()


template<class X, int Y>
struct T_my_cast_
{
    typedef X result_type;

    X operator()(int i) const
    {
        return i;
    }
};

#define  PSTADE_EGG_SPECIFIED_PARAMS (my_cast_, T_my_cast_, (class)(int), (1))
#include PSTADE_EGG_SPECIFIED()


struct x
{
    x() : m_i(7)
    { }

    explicit x(int i) 
        : m_i(i) 
    { }
    
    x(int i, int j)
        : m_i(i+j)
    { }

    x(int i, int j, int k)
        : m_i(i+j+k)
    { }

    int m_i;
};


struct const_ { };
struct mutable_ { };


template<class X>
struct T_array_check
{
    template<class FunCall>
    struct result;

    template<class Fun, class Array>
    struct result<Fun(Array&)> :
        boost::mpl::if_< boost::is_const<Array>,
            const_, mutable_
        >
    { };

#if 0 // cannot specialze 'Array const' under VC7.1 
    template<class Fun, class Array>
    struct result<Fun(Array const&)>
    {
        typedef const_ type;
    };
#endif

    template<class Array>
    mutable_ operator()(Array& ) const
    {
        return mutable_();
    }

    template<class Array>
    const_ operator()(Array const& ) const
    {
        return const_();
    }

    T_array_check() { } // for Boost v1.33 result_of
};

#define  PSTADE_EGG_SPECIFIED_PARAMS (array_check, T_array_check, 1, (1))
#include PSTADE_EGG_SPECIFIED()


void pstade_minimal_test()
{
    {
        BOOST_CHECK( ::my_cast<int>(3) == 3 );
        BOOST_CHECK(( ::my_cast_<int, 1>(3) == 3 ));
    }
    {
        int arr[10] = { };
        mutable_ m = ::array_check<int>(arr);
        (void)m;
    }
    {
        int const arr[10] = { };
        const_ c = ::array_check<int>(arr);
        (void)c;
    }
}
