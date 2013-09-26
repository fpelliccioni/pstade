#ifndef PSTADE_OVEN_DETAIL_IDENTITY_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_IDENTITY_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/egg/copy.hpp>
#include "../do_iter_swap.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Traversal, class Difference, class Tag >
struct identity_iterator;


template< class Iterator, class Traversal, class Difference, class Tag >
struct identity_iterator_super
{
    typedef
        boost::iterator_adaptor<
            identity_iterator<Iterator, Traversal, Difference, Tag>,
            Iterator,
            boost::use_default,
            Traversal,
            boost::use_default,
            Difference
        >
    type;
};


template< class Iterator, class Traversal, class Difference, class Tag >
struct identity_iterator :
    identity_iterator_super<Iterator, Traversal, Difference, Tag>::type
{
private:
    typedef typename identity_iterator_super<Iterator, Traversal, Difference, Tag>::type super_t;
    typedef typename super_t::difference_type diff_t;

public:
    typedef Tag tag_type;

    explicit identity_iterator()
    { }

    explicit identity_iterator(Iterator it) :
        super_t(it)
    { }

    template< class I, class T, class D, class G >
    identity_iterator(identity_iterator<I, T, D, G> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
friend class boost::iterator_core_access;
    template< class I, class T, class D, class G >
    diff_t distance_to(identity_iterator<I, T, D, G> const& other) const
    {
        return egg::copy<diff_t>(other.base() - this->base());
    }
};


template< class I1, class T1, class D1, class G1, class I2, class T2, class D2, class G2 > inline
void iter_swap(identity_iterator<I1, T1, D1, G1> it1, identity_iterator<I2, T2, D2, G2> it2, int = 0)
{
    do_iter_swap(it1.base(), it2.base());
}


} } } // namespace pstade::oven::detail


#endif
