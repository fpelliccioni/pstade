#ifndef PSTADE_EGG_COMPOSE_HPP
#define PSTADE_EGG_COMPOSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    // The nullary result type must be explicitly specified.
    // 'result_of<F(result_of<G()>::type)>::type' is always instantiated,
    // but it may be ill-formed, if 'result_of<G()>::type' is 'void', or
    // an invalid type like 'tuples::null_type' which Boost.Lambda returns instead of 'void'.
    // If such an invalid type is always 'void', then 'result_of<F()>::type' is always well-formed.
    // But, it is not a general solution. "compose2" to call 'f(g1, g2)' would be ill-formed after all.


    namespace compose_detail {


        template<class F, class G>
        struct little_fused_result
        {
            F m_f;
            G m_g;

            template<class Myself, class ArgTuple>
            struct apply :
                result_of<
                    F const(typename result_of<typename result_of<T_fuse(G const&)>::type(ArgTuple&)>::type)
                >
            { };

            template<class Result, class ArgTuple>
            Result call(ArgTuple& args) const
            {
                return m_f(fuse(m_g)(args));
            }
        };


    } // namespace compose_detail


    template<class F, class G, class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct result_of_compose :
        result_of_unfuse<
            function<compose_detail::little_fused_result<F, G>, by_cref>,
            boost::use_default,
            NullaryResult,
            Strategy
        >
    { };


    // PSTADE_EGG_UNFUSE_L { { F, G } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_COMPOSE_L PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_COMPOSE_M ,
    #define PSTADE_EGG_COMPOSE_R } } PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_COMPOSE(F, G) PSTADE_EGG_COMPOSE_L F PSTADE_EGG_COMPOSE_M G PSTADE_EGG_COMPOSE_R


    namespace compose_detail {


        template<class NullaryResult>
        struct little
        {
            template<class Myself, class F, class G>
            struct apply :
                result_of_compose<F, G, NullaryResult>
            { };

            template<class Result, class F, class G>
            Result call(F f, G g) const
            {
                Result r = PSTADE_EGG_COMPOSE(f, g);
                return r;
            }
        };


    } // namespace compose_detail


    template<class NullaryResult = boost::use_default>
    struct X_compose :
        function<compose_detail::little<NullaryResult>, by_value>
    { };


    typedef X_compose<>::function_type T_compose;
    PSTADE_POD_CONSTANT((T_compose), compose) = {{}};


} } // namespace pstade::egg


#endif
