#ifndef PSTADE_HAMBURGER_MOVER_HPP
#define PSTADE_HAMBURGER_MOVER_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/ketchup/core.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include "./factory.hpp"
#include "./point.hpp"
#include "./rectangle.hpp"


namespace pstade { namespace hamburger {


    namespace mover_detail {


        PSTADE_INSTANCE((ustring) const, Name_direction, ("direction"))

            PSTADE_INSTANCE((ustring) const, Value_bottom,        ("bottom"))
            PSTADE_INSTANCE((ustring) const, Value_bottomLeft,    ("bottomLeft"))
            PSTADE_INSTANCE((ustring) const, Value_bottomRight,   ("bottomRight"))
            PSTADE_INSTANCE((ustring) const, Value_left,          ("left"))
            PSTADE_INSTANCE((ustring) const, Value_right,         ("right"))
            PSTADE_INSTANCE((ustring) const, Value_top,           ("top"))
            PSTADE_INSTANCE((ustring) const, Value_topLeft,       ("topLeft"))
            PSTADE_INSTANCE((ustring) const, Value_topRight,      ("topRight"))
            PSTADE_INSTANCE((ustring) const, Value_free,          ("free"))


        template< class Node >
        LRESULT ht_value(Node& node)
        {
            ustring val = node%Name_direction;

            if (false)
                ;
            else if (oven::equals(val, Value_bottom))
                return HTBOTTOM;
            else if (oven::equals(val, Value_bottomLeft))
                return HTBOTTOMLEFT;
            else if (oven::equals(val, Value_bottomRight))
                return HTBOTTOMRIGHT;
            else if (oven::equals(val, Value_left))
                return HTLEFT;
            else if (oven::equals(val, Value_right))
                return HTRIGHT;
            else if (oven::equals(val, Value_top))
                return HTTOP;
            else if (oven::equals(val, Value_topLeft))
                return HTTOPLEFT;
            else if (oven::equals(val, Value_topRight))
                return HTTOPRIGHT;
            else if (oven::equals(val, Value_free))
                return HTCAPTION;

            return HTCLIENT;
        }


    } // namespace mover_detail


    struct mover :
        ketchup::message_processor<mover,
            element
        >
    {
    protected:
        void override_create()
        {
            m_ht = mover_detail::ht_value(*this);
        }

        void override_set_bounds(rectangle const& rc)
        {
            m_bounds = rc;
        }

        rectangle override_bounds() const
        {
            return m_bounds;
        }

    private:
        rectangle m_bounds;
        LRESULT m_ht;

    friend class ketchup::access;
        LRESULT on_nchittest(point pt)
        {
            if (m_ht == HTCLIENT)
                set_msg_handled(false);

            pstade::unused(pt);
            return m_ht;
        }

        begin_msg_map
        <
            msg_wm_nchittest<&_::on_nchittest>
        >
        end_msg_map;
    };


    namespace mover_detail {


        PSTADE_STATEMENT(Register,
            hamburger::register_element<mover>("mover");
        )


    } // namespace mover_detail


} } // namespace pstade::hamburger


#endif
