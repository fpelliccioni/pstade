#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_CONCEPT_CHECK
#include <iostream>
#include <pstade/oven/hetero.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/any.hpp>
#include <pstade/egg/from.hpp>
#include <boost/optional/optional.hpp>


namespace oven = pstade::oven;
using namespace oven;


struct shape
{
    virtual void draw() {};
    virtual ~shape() {}
};

struct rectangle : shape
{
    virtual void draw() { std::cout << "rectangle" << std::endl; }
};

struct triangle : shape
{
    virtual void draw() { std::cout << "triangle" << std::endl; }
};

struct circle : shape
{
    virtual void draw() { std::cout << "circle" << std::endl; }
};


void pstade_minimal_test()
{
    using pstade::any_ref;
    using pstade::egg::from_any;
    namespace egg = pstade::egg;

    {
        rectangle r; triangle t; circle c;
        boost::tuple<rectangle*, triangle*, circle*> tup(&r, &t, &c);
        BOOST_FOREACH (shape *s, oven::hetero<shape *>(tup)) {
            s->draw();
        }
    }

    {
        boost::tuple<int, char, std::string> tup(1, 'a', "hello");

        BOOST_FOREACH (any_ref a, oven::hetero<any_ref>(tup)) {
            if (boost::optional<std::string &> o = from_any(a)) {
                *o = "goodbye";
                break;
            }
        }

        BOOST_CHECK( boost::get<2>(tup) == "goodbye" );
    }
}
