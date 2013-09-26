#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BY_CREF_HPP
#define PSTADE_EGG_BY_CREF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/preprocessor.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/call_little.hpp"
#include "./detail/meta_arg.hpp"
#include "./detail/nullary_result.hpp"
#include "./function_fwd.hpp"
#include "./sig_template.hpp"


namespace pstade { namespace egg {


    template<class Little>
    struct function<Little, by_cref>
    {
        typedef function function_type;
        typedef Little little_type;

        Little m_little;

        Little little() const
        {
            return m_little;
        }

    // 0ary
        typedef typename
            detail::nullary_result<Little, function>::type
        nullary_result_type;

        nullary_result_type operator()() const
        {
            return detail::call_little<
                Little, nullary_result_type
            >::call(m_little);
        }

    // 1ary-
        template<class FunCall>
        struct result;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/by_cref.hpp>))
        #include BOOST_PP_ITERATE()

        #include PSTADE_EGG_SIG_TEMPLATE()
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        Little::template apply<
            Little const,
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename detail::meta_carg<A, >::type)
        >
    { };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<
            BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)) const
    {
        return detail::call_little<
            Little, typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
        >::call(m_little, BOOST_PP_ENUM_PARAMS(n, a));
    }
    

#undef n
#endif
