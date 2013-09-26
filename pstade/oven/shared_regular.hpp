#ifndef PSTADE_OVEN_SHARED_REGULAR_HPP
#define PSTADE_OVEN_SHARED_REGULAR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This is considered as a generalized 'regular_c'.


#include <pstade/egg/deferred.hpp>
#include <pstade/egg/indirect.hpp>
#include <pstade/egg/to_shared_ptr.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>


namespace pstade { namespace oven {


namespace shared_regular_detail {


    template< class Ptr >
    struct base
    {
        typedef typename
            result_of<
                egg::T_indirect(
                    typename result_of<egg::T_to_shared_ptr(Ptr&)>::type
                )
            >::type
        result_type;

        result_type operator()(Ptr& pf) const
        {
            return egg::indirect(egg::to_shared_ptr(pf));
        }
    };


} // namespace shared_regular_detail


typedef PSTADE_EGG_DEFER((shared_regular_detail::base<boost::mpl::_>)) T_shared_regular;
PSTADE_POD_CONSTANT((T_shared_regular), shared_regular) = PSTADE_EGG_DEFERRED;


} } // namespace pstade::oven


#endif
