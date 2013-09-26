#ifndef PSTADE_HAMBURGER_LOAD_SAVE_HPP
#define PSTADE_HAMBURGER_LOAD_SAVE_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // back_inserter
#include <vector>
#include <boost/range/begin.hpp>
#include <pstade/gravy/file_range.hpp>
#include <pstade/lime/copy_XMLDecl.hpp>
#include <pstade/lime/load.hpp>
#include <pstade/lime/save.hpp>
#include <pstade/oven/algorithm.hpp> // copy
#include <pstade/oven/applier.hpp>
#include <pstade/oven/utf8_decoded.hpp>
#include <pstade/tomato/to_tstring_to.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>


namespace pstade { namespace hamburger {


    template< class Node >
    void load(Node& node, ustring const& path)
    {
        // cache for speed
        std::vector<ucs4_t> tmp;
        gravy::ifile_range<utf8cp_t> irng(path|tomato::to_tstring);
        oven::copy(irng|oven::utf8_decoded, std::back_inserter(tmp));

        lime::load(node, tmp);
    }


    template< class Node > inline
    void save(Node& node)
    {
        lime::save(node, oven::applier(unused));
    }


    template< class Node >
    void save(Node& node, ustring const& path)
    {
        std::vector<utf8cp_t> tmp;
        lime::copy_XMLDecl(std::back_inserter(tmp));
        lime::save_default(node, oven::utf8_encoder|=std::back_inserter(tmp));

        gravy::ofile_range<utf8cp_t> orng(path|tomato::to_tstring, tmp.size());
        oven::copy(tmp, boost::begin(orng));
    }


} } // namespace pstade::hamburger


#endif
