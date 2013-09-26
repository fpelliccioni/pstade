#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/unlambda.hpp>
#include <pstade/egg/bind.hpp>
#include <pstade/egg/placeholders.hpp>
#include <pstade/minimal_test.hpp>


namespace egg = pstade::egg;
using namespace egg::placeholders;


int foo(int) { return 0; }
int bar(int, int) { return 0; }


template<class F>
int nested(const F& f) {
    int x;
    egg::bind(egg::unlambda(f), _1)(x);
    return x;
}


void pstade_minimal_test()
{
    ::nested(egg::bind(&bar, 1, _1));
}










#if 0

#include <boost/bind.hpp>
#include <pstade/minimal_test.hpp>

using namespace boost;

int foo(int) { return 0; }
int bar(int, int) { return 0; }

template<class F>
int nested(const F& f) {
  int x;
  bind(f, _1)(x);
  return x;
}

void pstade_minimal_test()
{
    nested(bind(&bar, 1, _1));
}

#endif




#if 0

#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/minimal_test.hpp>

using namespace boost::lambda;

int foo(int) { return 0; }
int bar(int, int) { return 0; }

template<class F>
int nested(const F& f) {
  int x;
  bind(f, _1)(x);
  return x;
}

void pstade_minimal_test()
{
    nested(bind(&bar, 1, _1));
}

#endif
