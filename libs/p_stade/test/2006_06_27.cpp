#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iostream>
#include <boost/algorithm/string.hpp>
#include <pstade/locale_saver.hpp>


void test()
{
    using namespace pstade;

    locale_saver ls(std::wcout, "japanese");

    std::wstring str(L"��");

    // scoped_locale ls1("japanese"); // breaks vc8 wstreams.

    {
        locale_saver ls("japanese"); // global
        boost::to_upper(str);
        BOOST_CHECK(( boost::equals(str, std::wstring(L"�`")) ));
    }

    std::wcout << str << std::endl;
    std::wcout << L"kkkkkkk����" << std::endl;
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}

