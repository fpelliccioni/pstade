#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



//#include "./pod_constant_.hpp"
#include "./static_initialization.hpp"


T_my_id const &get_my_id1( )
{
   return my_id;
}

int i = get_my_id2().little().touch;


T_my_idr const &get_my_idr1( )
{
   return my_idr;
}

int ir = get_my_idr2().little().base().little().touch;


T_my_func const &get_my_func1( )
{
   return my_func;
}


T_my_idrr const &get_my_idrr1( )
{
   return my_idrr;
}

int irr = get_my_idrr2().little().base().little().base().little().touch;

int ifun = get_my_func2().
    little().
    base().
    little().
    m_arg.
    little().
    m_arg.
    little().
    m_arg.
    little().
    touch;


T_pipa const &get_pipa1( )
{
   return pipa;
}

int ipi = get_pipa2().little().base().touch;


T_auxi const &get_auxi1( )
{
   return auxi;
}

int iau = get_auxi2().little().base().touch;


