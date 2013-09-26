#ifndef PSTADE_HAMBURGER_BUTTON_HPP
#define PSTADE_HAMBURGER_BUTTON_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/ketchup/core.hpp>
#include <pstade/statement.hpp>
#include "./element.hpp"
#include "./factory.hpp"


namespace pstade { namespace hamburger {


    struct button :
        ketchup::message_processor<button, element>
    {
        begin_msg_map
        <
            empty_entry<>
        >
        end_msg_map;
    };


    namespace button_detail {


        PSTADE_STATEMENT(Register,
            hamburger::register_element<button>("button");
        )


    } // namespace button_detail


} } // namespace pstade::hamburger


#endif
