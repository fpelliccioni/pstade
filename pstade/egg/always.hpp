#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_ALWAYS_HPP
#define PSTADE_EGG_ALWAYS_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include "./by_cref.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./generator.hpp"
#include "./little_apply.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    namespace always_detail {


        template<class X>
        struct little
        {
            X m_x;

        // 0ary
            typedef X nullary_result_type;

            template<class Result>
            Result call() const
            {
                return m_x;
            }

        // 1ary-
            template<class Myself, PSTADE_EGG_LITTLE_APPLY_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
            struct apply
            {
                typedef X type;
            };

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/always.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace always_detail


    template<class X>
    struct result_of_always
    {
        typedef
            function<always_detail::little<X>, by_cref>
        type;
    };

    #define PSTADE_EGG_ALWAYS_L { {
    #define PSTADE_EGG_ALWAYS_R } }
    #define PSTADE_EGG_ALWAYS(F) PSTADE_EGG_ALWAYS_L F PSTADE_EGG_ALWAYS_R

    typedef
        generator<
            result_of_always< deduce<boost::mpl::_1, as_wrapped_ref> >::type,
            boost::use_default,
            use_brace2,
            by_cref
        >::type
    T_always;

    PSTADE_POD_CONSTANT((T_always), always) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)) const
    {
        return m_x;
    }


#undef n
#endif
