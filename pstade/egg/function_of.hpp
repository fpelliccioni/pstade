#ifndef PSTADE_EGG_FUNCTION_OF_HPP
#define PSTADE_EGG_FUNCTION_OF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./function_fwd.hpp"
#include "./detail/forwarding_strategy.hpp"


namespace pstade { namespace egg {


    template<class Little, class Strategy = boost::use_default>
    struct function_of
    {
        typedef
            function<Little, typename detail::forwarding_strategy<Little, Strategy>::type>
        type;
    };


} } // namespace pstade::egg


#endif
