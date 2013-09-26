#ifndef PSTADE_VALUE_BASED_HPP
#define PSTADE_VALUE_BASED_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <boost/pointee.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/reset_assignment.hpp>
#include <pstade/radish/swap_reset.hpp>
#include <pstade/radish/swappable.hpp>
#include <pstade/radish/value_pointable.hpp>


namespace pstade {


    template<class Ptr>
    struct value_based :
        radish::bool_testable  < value_based<Ptr>,
        radish::swappable      < value_based<Ptr>,
        radish::value_pointable< value_based<Ptr>, typename boost::pointee<Ptr>::type,
        boost::totally_ordered1< value_based<Ptr> > > > >
    {
    private:
        typedef value_based self_t;
        typedef typename boost::pointee<Ptr>::type pointee_t;

    public:
    // structors
        value_based(boost::none_t = boost::none)
        { }

        template<class Q>
        value_based(Q const &q, typename enable_if< is_convertible<Q *, pointee_t *> >::type = 0) :
            m_ptr(new Q(q))
        { }

    // assignments
        typedef value_based pstade_radish_this_type;
        #include PSTADE_RADISH_SWAP_RESET()
        #include PSTADE_RADISH_RESET_ASSIGNMENT()

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(m_ptr);
        }

    // value_pointable (const affects.)
        pointee_t *operator->()
        {
            BOOST_ASSERT(m_ptr);
            return m_ptr.get();
        }

        pointee_t const *operator->() const
        {
            BOOST_ASSERT(m_ptr);
            return m_ptr.get();
        }

    // swappable
        void swap(self_t &other)
        {
            m_ptr.swap(other.m_ptr);
        }

    // totally_ordered
        bool operator< (self_t const &other) const
        {
            return boost::less_pointees(*this, other);
        }

        bool operator==(self_t const &other) const
        {
            return boost::equal_pointees(*this, other);
        }

    private:
        Ptr m_ptr;
    };


} // namespace pstade


// Dereferenceable extension
//

#include <boost/pointee.hpp>
#include <pstade/egg/extension.hpp>


namespace pstade_egg_extension {


    template< class Ptr >
    struct Dereferenceable< pstade::value_based<Ptr> >
    {
        typedef typename
            boost::pointee<Ptr>::type &
        reference;
    };

    template< class Ptr >
    struct Dereferenceable< pstade::value_based<Ptr> const >
    {
        typedef typename
            boost::pointee<Ptr>::type const &
        reference;
    };


} // namespace pstade_egg_extension


#endif
