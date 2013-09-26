#ifndef PSTADE_GRAVY_SCOPED_FILE_VIEW_HPP
#define PSTADE_GRAVY_SCOPED_FILE_VIEW_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/verify.hpp>
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    namespace scoped_file_view_detail {


        struct impl :
            private boost::noncopyable
        {
            explicit impl(LPVOID pView) :
                m_pView(pView)
            {
                BOOST_ASSERT( m_pView != NULL );
            }

            ~impl()
            {
                pstade::verify( ::UnmapViewOfFile(m_pView) );
            }

            LPVOID const m_pView;
        };


    } // namespace scoped_file_view_detail


    struct scoped_file_view :
        radish::bool_testable<scoped_file_view, boost::noncopyable>
    {
        explicit scoped_file_view(LPVOID pView = NULL)
        {
            reset(pView);
        }

        void reset(LPVOID pView = NULL)
        {
            m_pimpl.reset(pView != NULL ? new scoped_file_view_detail::impl(pView) : PSTADE_NULLPTR);
        }

        LPVOID operator *() const
        {
            return m_pimpl->m_pView;
        }

        LPVOID get() const
        {
            return m_pimpl ? m_pimpl->m_pView : NULL;
        }

        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(m_pimpl);
        }

    private:
        boost::scoped_ptr<scoped_file_view_detail::impl> m_pimpl;
    };


} } // namespace pstade::gravy


#endif
