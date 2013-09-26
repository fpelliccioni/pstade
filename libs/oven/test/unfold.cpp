#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/unfold.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <utility> // pair
#include <boost/optional/optional.hpp>
#include <string>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/range_traversal.hpp>
#include <boost/lexical_cast.hpp>


struct my_inc
{
    std::string m_to;

    my_inc() { }
    my_inc(std::string to) : m_to(to) { }

    typedef boost::optional<int> result_type;

    result_type operator()(std::string const& s) const
    {
        if (s == m_to)
            return result_type(); // the end.

        return boost::lexical_cast<int>(s);
    }
};

struct my_next
{
    // no result_type ok.

    std::string operator()(std::string const& s) const
    {
        int i = boost::lexical_cast<int>(s);
        return boost::lexical_cast<std::string>(i+1);
    }
};



struct my_nonpure_inc :
    my_inc
{
    typedef my_nonpure_inc is_nonpure;

    my_nonpure_inc() : my_inc("10")
    { }
};


boost::optional<int>
inc_fun(int i)
{
    if (i == 10)
        return boost::optional<int>();

    return i;
}

int next_fun(int i)
{
    return i+1;
}


void check_single_pass_aux(boost::single_pass_traversal_tag)
{
}

void check_single_pass_aux(boost::forward_traversal_tag)
{
    BOOST_CHECK(false && "check_single_pass failed.");
}


template<class Range>
void check_single_pass(Range& rng)
{
    ::check_single_pass_aux(typename pstade::oven::range_traversal<Range>::type());
}


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::forward_constant(unfold(std::string("0"), my_inc("10"), my_next()), a);
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::single_pass_readable(unfold(std::string("0"), nonpure(my_inc("10")), my_next()), a);
        ::check_single_pass( unfold(std::string("0"), nonpure(my_inc("10")), my_next()) );
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::single_pass_readable(unfold(std::string("0"), my_nonpure_inc(), my_next()), a);
        ::check_single_pass( unfold(std::string("0"), my_nonpure_inc(), my_next()) );
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::forward_constant(unfold(0, &::inc_fun, &::next_fun), a);
    }
    {
        int a[] = { 0,1,2,3,4,5,6,7,8,9 };
        test::single_pass_readable(unfold(0, nonpure(&::inc_fun), &::next_fun), a);
    }
}
