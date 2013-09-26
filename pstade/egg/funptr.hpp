#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_FUNPTR_HPP
#define PSTADE_EGG_FUNPTR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...


#include <boost/optional/optional.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "./by_value.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./specified.hpp"


namespace pstade { namespace egg {


    namespace funptr_detail {


        template<class Base, class Signature, class UniqueID>
        struct aux_;


        // 0ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/funptr.hpp>))
        #include BOOST_PP_ITERATE()


    } // namespace funptr_detail


    template<class Base, class Signature, class UniqueID>
    struct result_of_funptr
    {
        typedef typename
            funptr_detail::aux_<Base, Signature, UniqueID>::pointer_type
        type;
    };


    namespace funptr_detail {


        template<class Signature, class UniqueID>
        struct little
        {
            template<class Myself, class Base>
            struct apply :
                result_of_funptr<Base, Signature, UniqueID>
            { };

            template<class Result, class Base>
            Result call(Base base) const
            {
                typedef aux_<Base, Signature, UniqueID> aux_t;
                aux_t::base_instance() = base;
                return &aux_t::call;
            }
        };


    } // namespace funptr_detail


    template<class Signature, class UniqueID>
    struct X_funptr :
        function<funptr_detail::little<Signature, UniqueID>, by_value>
    { };


    #define  PSTADE_EGG_SPECIFIED_PARAMS (funptr, X_funptr, (class)(class), (1))
    #include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, class ResultType BOOST_PP_ENUM_TRAILING_PARAMS(n, class A), class UniqueID>
    struct aux_<Base, ResultType(BOOST_PP_ENUM_PARAMS(n, A)), UniqueID>
    {
        typedef typename
            eval_if_use_default<ResultType,
                result_of<Base(PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::add_reference<A, >::type))>
            >::type
        result_type;

        typedef result_type (*pointer_type)(BOOST_PP_ENUM_PARAMS(n, A));

        static boost::optional<Base>& base_instance()
        {
            static boost::optional<Base> b; // Use optional for DefaultConstructible.
            return b;
        };

        static result_type call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a))
        {
            return (*base_instance())(BOOST_PP_ENUM_PARAMS(n, a));
        }
    };


#undef n
#endif
