#ifndef PSTADE_EGG_DEFERRED_HPP
#define PSTADE_EGG_DEFERRED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include "./detail/as_mpl_lambda.hpp"
#include "./detail/little_deferred.hpp"
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    template<class Lambda, class Strategy = by_perfect>
    struct deferred
    {
        typedef
            function<detail::little_deferred<Lambda>, Strategy>
        type;
    };


    #define PSTADE_EGG_DEFERRED {{}}


    // If you are a msvc-8.0 user, prefer this macro.
    // Note that PSTADE_EGG_AS_MPL_LAMBDA in 'deferred' can't work around.
    #define PSTADE_EGG_DEFER(L) \
        pstade::egg::deferred<PSTADE_EGG_AS_MPL_LAMBDA(L)>::type \
    /**/

    #define PSTADE_EGG_DEFER_BY(L, By) \
        pstade::egg::deferred<PSTADE_EGG_AS_MPL_LAMBDA(L), By>::type \
    /**/


} } // namespace pstade::egg


#endif
