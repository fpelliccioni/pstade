#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_LAZY_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_LAZY_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "../bll/bind.hpp"
#include "../bll/result_of.hpp" // inclusion guaranteed
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../by_cref.hpp"
#include "../little_apply.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base, class Bind>
    struct little_lazy_result
    {
        typedef Base base_type;
        typedef typename if_use_default<Bind, T_bll_bind>::type bind_type;

        Base m_base;
        bind_type m_bind;

        Base base() const
        {
            return m_base;
        }

    // 0ary
        typedef typename
            result_of<bind_type const(Base const&)>::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return m_bind(m_base);
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_LITTLE_APPLY_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
        struct PSTADE_EGG_LITTLE_APPLY;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/little_lazy_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            bind_type const(Base const&, PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_bind(m_base, BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
