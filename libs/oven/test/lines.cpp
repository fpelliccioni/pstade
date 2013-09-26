#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/lines.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <boost/range/sub_range.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <boost/foreach.hpp>


namespace lambda = boost::lambda;
namespace oven = pstade::oven;
using namespace oven;


void pstade_minimal_test()
{
    {
        std::string _("012345678901234567890");
        std::string b("abcNdeNfghNNiNjNklmNN");
        std::string::iterator first = b.begin();
        std::vector< iter_range<std::string::iterator> > a;

        a.push_back(make_iter_range(first, first+3)); a.push_back(make_iter_range(first+4, first+6));
        a.push_back(make_iter_range(first+7, first+10)); a.push_back(make_iter_range(first+11, first+11));
        a.push_back(make_iter_range(first+12, first+13)); a.push_back(make_iter_range(first+14, first+15));
        a.push_back(make_iter_range(first+16, first+19)); a.push_back(make_iter_range(first+20, first+20));
        test::bidirectional_constant(b|lines('N'), a);
    }
    {
        std::string _("012345678901234567890");
        std::string b("abc\nde\nfgh\n\ni\nj\nklm\n\n");
        std::string::iterator first = b.begin();
        std::vector< iter_range<std::string::iterator> > a;

        a.push_back(make_iter_range(first, first+3)); a.push_back(make_iter_range(first+4, first+6));
        a.push_back(make_iter_range(first+7, first+10)); a.push_back(make_iter_range(first+11, first+11));
        a.push_back(make_iter_range(first+12, first+13)); a.push_back(make_iter_range(first+14, first+15));
        a.push_back(make_iter_range(first+16, first+19)); a.push_back(make_iter_range(first+20, first+20));
        test::bidirectional_constant(b|lines, a);
    }
    {
        std::string _("012345678901234567890");
        std::string b("NbcNdeNfghNNiNjNklmNN");
        std::string::iterator first = b.begin();
        std::vector< iter_range<std::string::iterator> > a;

        a.push_back(make_iter_range(first, first));
        a.push_back(make_iter_range(first+1, first+3)); a.push_back(make_iter_range(first+4, first+6));
        a.push_back(make_iter_range(first+7, first+10)); a.push_back(make_iter_range(first+11, first+11));
        a.push_back(make_iter_range(first+12, first+13)); a.push_back(make_iter_range(first+14, first+15));
        a.push_back(make_iter_range(first+16, first+19)); a.push_back(make_iter_range(first+20, first+20));
        test::bidirectional_constant(b|lines('N'), a);
    }
    {
        std::string b;
        test::emptiness(b|lines);
    }
    {
        std::string rng("abc\nde\nfgh\n\ni\nj\nklm\n\n");
        BOOST_FOREACH (boost::sub_range<std::string> s, rng|lines) {
            std::cout << boost::copy_range<std::string>(s) << std::endl;
        }
    }
}
