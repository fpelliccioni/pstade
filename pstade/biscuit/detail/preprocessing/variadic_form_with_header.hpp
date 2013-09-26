
/*
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_header
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_param_header
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_param
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_default_arg
#define PSTADE_BISCUIT_VARIADIC_FORM_ARG_make_inside
*/

#if !defined(BOOST_PP_IS_ITERATING)

        #include <boost/preprocessor/cat.hpp>
        #include <boost/preprocessor/iteration/iterate.hpp>
        #include <boost/preprocessor/iteration/local.hpp>
        #include <boost/preprocessor/punctuation/comma_if.hpp>
        #include <boost/preprocessor/repetition/enum_params.hpp>
        #include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

        #if !defined(PSTADE_BISCUIT_VARIADIC_FORM_ARG_header)
            #define PSTADE_BISCUIT_VARIADIC_FORM_ARG_header
        #endif

        #if !defined( PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer)
            #define PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer
        #endif

        #if !defined(PSTADE_BISCUIT_VARIADIC_FORM_ARG_param_header)
            #define PSTADE_BISCUIT_VARIADIC_FORM_ARG_param_header
        #endif

        #if !defined(PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header)
            #define PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header
        #endif

        #if !defined(PSTADE_BISCUIT_VARIADIC_FORM_ARG_make_inside)
            #define PSTADE_BISCUIT_VARIADIC_FORM_ARG_make_inside(name, i)
        #endif

        PSTADE_BISCUIT_VARIADIC_FORM_ARG_header

// primary
template<
    PSTADE_BISCUIT_VARIADIC_FORM_ARG_param_header BOOST_PP_COMMA_IF(PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits)
    BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits, PSTADE_BISCUIT_VARIADIC_FORM_ARG_param PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg, PSTADE_BISCUIT_VARIADIC_FORM_ARG_default_arg)
>
struct PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename :
    BOOST_PP_CAT(PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename, PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits)<
        PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header BOOST_PP_COMMA_IF(PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits)
        BOOST_PP_ENUM_PARAMS(PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits, PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg)
    >
{
    PSTADE_BISCUIT_VARIADIC_FORM_ARG_make_inside(PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename, PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits)
};

        #define BOOST_PP_ITERATION_LIMITS (0, PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits-1)
        #define BOOST_PP_FILENAME_1 "./variadic_form_with_header.hpp"
        #include BOOST_PP_ITERATE()

        PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer

        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_header
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_footer
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_limits
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_param_header
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_param
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_default_arg
        #undef PSTADE_BISCUIT_VARIADIC_FORM_ARG_make_inside

#else // BOOST_PP_IS_ITERATING

    #define i BOOST_PP_ITERATION()

template<
    PSTADE_BISCUIT_VARIADIC_FORM_ARG_param_header BOOST_PP_COMMA_IF(i)
    BOOST_PP_ENUM_PARAMS(i, PSTADE_BISCUIT_VARIADIC_FORM_ARG_param PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg)
>
struct PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename<
    PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header BOOST_PP_COMMA_IF(i)
    BOOST_PP_ENUM_PARAMS(i, PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg)
> :
    BOOST_PP_CAT(PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename, i)<
        PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg_header BOOST_PP_COMMA_IF(i)
        BOOST_PP_ENUM_PARAMS(i, PSTADE_BISCUIT_VARIADIC_FORM_ARG_arg)
    >
{
    PSTADE_BISCUIT_VARIADIC_FORM_ARG_make_inside(PSTADE_BISCUIT_VARIADIC_FORM_ARG_typename, i)
};

    #undef i

#endif // BOOST_PP_IS_ITERATING
