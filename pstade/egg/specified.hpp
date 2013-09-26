#ifndef PSTADE_EGG_SPECIFIED_HPP
#define PSTADE_EGG_SPECIFIED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Does perfect forwarding for cast form functions.
// The "result_of revolution" turns a namespace scope function
// into nothing but a syntax sugar, though.


// Usage:
//
// namespace my {
//     template<class T> struct T_my_cast { .. };
//     #define  PSTADE_EGG_SPECIFIED_PARAMS (my_cast, T_my_cast, (class), (1)(3))
//     #include PSTADE_EGG_SPECIFIED()
// }
//
// 5 or more arity is not recommended; it tends to make so many functions.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "./detail/result_of_in_ns_scope.hpp"


#define PSTADE_EGG_SPECIFIED() <pstade/egg/detail/specified_include.hpp>


#endif
