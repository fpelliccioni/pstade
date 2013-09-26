#ifndef PSTADE_OVEN_DETAIL_CONST_REF_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_CONST_REF_ITERATOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/optional/optional.hpp>
#include "../read.hpp"
#include "./pure_traversal.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct const_ref_iterator;


template< class Iterator >
struct const_ref_iterator_super
{
    typedef
        typename boost::iterator_value<Iterator>::type
    val_t;

    typedef
        boost::iterator_adaptor<
            const_ref_iterator<Iterator>,
            Iterator,
            val_t,
            typename pure_traversal<Iterator>::type,
            val_t const&
        >
    type;
};


template< class Iterator >
struct const_ref_iterator :
    const_ref_iterator_super<Iterator>::type
{
private:
    typedef typename const_ref_iterator_super<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::value_type val_t;

public:
    explicit const_ref_iterator()
    { }

    explicit const_ref_iterator(Iterator it) :
        super_t(it)
    { }

    template< class I >
    const_ref_iterator(const_ref_iterator<I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

private:
    mutable boost::optional<val_t> m_value;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_value)
            m_value = read(this->base());

        return *m_value;
    }

    void increment()
    {
        ++this->base_reference();
        m_value.reset();
    }

    void decrement()
    {
        --this->base_reference();
        m_value.reset();
    }

    template< class Difference >
    void advance(Difference n)
    {
        this->base_reference() += n;
        m_value.reset();
    }
};


} } } // namespace pstade::oven::detail


#endif
