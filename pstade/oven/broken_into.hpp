#ifndef PSTADE_OVEN_BROKEN_INTO_HPP
#define PSTADE_OVEN_BROKEN_INTO_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/token_iterator.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/specified.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace broken_into_detail {


    template< class Type >
    struct little
    {
        template< class Myself, class Range, class TokenizerFun >
        struct apply
        {
            typedef
                boost::token_iterator<
                    typename pass_by_value<TokenizerFun>::type,
                    typename range_iterator<Range>::type,
                    Type
                >
            iter_t;

            typedef
                iter_range<iter_t> const
            type;
        };

        template< class Result, class Range, class TokenizerFun >
        Result call(Range& rng, TokenizerFun& fun) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
            return aux<Result>(boost::begin(rng), boost::end(rng), fun);
        }

        template< class Result, class Iterator, class TokenizerFun >
        Result aux(Iterator first, Iterator last, TokenizerFun& fun) const
        {
            typedef typename Result::iterator iter_t;
            return Result(iter_t(fun, first, last), iter_t(fun, last, last));
        }
    };


} // namespace broken_into_detail


template< class Type >
struct X_make_broken_into :
    egg::function< broken_into_detail::little<Type> >
{ };


#define  PSTADE_EGG_SPECIFIED_PARAMS (make_broken_into, X_make_broken_into, (class), (1))
#include PSTADE_EGG_SPECIFIED()


namespace broken_into_detail_ {


    template< class Type, class TokenizerFun  >
    struct pipe
    {
        explicit pipe(TokenizerFun fun) :
            m_fun(fun)
        { }

        TokenizerFun m_fun;

    private:
        pipe& operator=(pipe const&);
    };


    template< class Range, class TokenizerFun, class Type > inline
    typename result_of<X_make_broken_into<Type>(Range&, TokenizerFun&)>::type
    operator|(Range& rng, pipe<Type, TokenizerFun> pi)
    {
        return X_make_broken_into<Type>()(rng, pi.m_fun);
    }

    template< class Range, class TokenizerFun, class Type > inline
    typename result_of<X_make_broken_into<Type>(PSTADE_DEDUCED_CONST(Range)&, TokenizerFun&)>::type
    operator|(Range const& rng, pipe<Type, TokenizerFun> pi)
    {
        return X_make_broken_into<Type>()(rng, pi.m_fun);
    }


} // namespace broken_into_detail_


template< class Type, class TokenizerFun > inline
broken_into_detail_::pipe<Type, TokenizerFun> const
broken_into(TokenizerFun fun)
{
    return broken_into_detail_::pipe<Type, TokenizerFun>(fun);
}


} } // namespace pstade::oven


#endif
