#ifndef PSTADE_BISCUIT_STATE_ACTIONABLE_GUARD_HPP
#define PSTADE_BISCUIT_STATE_ACTIONABLE_GUARD_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>


namespace pstade { namespace biscuit {


template< class State >
struct state_actionable_guard :
    private boost::noncopyable
{
    state_actionable_guard(State& s, bool act) :
        m_state(s), m_prev(s.is_actionable())
    { m_state.set_actionable(act); }

    ~state_actionable_guard()
    { m_state.set_actionable(m_prev); }

private:
    State& m_state;
    bool const m_prev;
};


} } // namespace pstade::biscuit


#endif
