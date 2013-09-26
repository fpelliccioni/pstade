#ifndef PSTADE_OVEN_UTF8_ENCODER_HPP
#define PSTADE_OVEN_UTF8_ENCODER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/regex/pending/unicode_iterator.hpp> // utf8_output_iterator
#include <pstade/pass_by.hpp>
#include "./detail/base_to_adaptor.hpp"


namespace pstade { namespace oven {


namespace utf8_encoder_detail {


    template< class OutIter >
    struct base
    {
        typedef
            boost::utf8_output_iterator<
                typename pass_by_value<OutIter>::type
            >
        result_type;

        result_type operator()(OutIter& it) const
        {
            return result_type(it);
        }
    };


} // namespace utf8_encoder_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(utf8_encoder, (utf8_encoder_detail::base<_>))


} } // namespace pstade::oven


#endif
