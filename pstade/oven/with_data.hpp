#ifndef PSTADE_OVEN_WITH_DATA_HPP
#define PSTADE_OVEN_WITH_DATA_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/enable_if.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./detail/unwrap_ref.hpp"
#include "./detail/data_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


// with_data
//

namespace with_data_detail {


    template< class Range, class Data >
    struct base
    {
        typedef
            detail::data_iterator<
                typename range_iterator<Range>::type,
                typename detail::unwrap_ref<Data>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Data& var) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return result_type(iter_t(boost::begin(rng), var), iter_t(boost::end(rng), var));
        }
    };


} // namespace with_data_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(with_data, (with_data_detail::base<_, _>))


// iter_data
//

template< class Data >
struct X_iter_data
{
    typedef X_iter_data function_type;
    typedef Data result_type;

    template< class Adapted >
    Data operator()(Adapted ad,
        typename enable_if< detail::has_data<Adapted, Data> >::type = 0) const
    {
        return ad.data();
    }

    template< class Adapted >
    Data operator()(Adapted ad,
        typename disable_if<detail::has_data<Adapted, Data> >::type = 0) const
    {
        return (*this)(ad.base());

    }
};

#define  PSTADE_EGG_SPECIFIED_PARAMS (iter_data, X_iter_data, (class), (1))
#include PSTADE_EGG_SPECIFIED()


// data
//

template< class Data >
struct X_data
{
    typedef X_data function_type;
    typedef Data result_type;

    template< class Adapted >
    Data operator()(Adapted const& ad) const
    {
        return X_iter_data<Data>()(ad.begin());
    }
};

#define  PSTADE_EGG_SPECIFIED_PARAMS (data, X_data, (class), (1))
#include PSTADE_EGG_SPECIFIED()


} } // namespace pstade::oven


#endif
