#ifndef PSTADE_GRAVY_FIND_FILE_RANGE_HPP
#define PSTADE_GRAVY_FIND_FILE_RANGE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Model of:
//
// Readable and Single Pass (Input) Range of WIN32_FIND_DATA


// Port of:
//
// boost::directory_iterator to non-shared_ptr version


#include <pstade/oven/iter_range.hpp>
#include <pstade/verify.hpp>
#include "./c_str.hpp"
#include "./detail/find_file_iterator.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    namespace find_file_range_detail {


        template<class = void>
        struct init
        {
            typedef init type;

        protected:
            HANDLE m_hFind;
            WIN32_FIND_DATA m_data;

            explicit init(TCHAR const *pszName)
            {
                m_hFind = ::FindFirstFile(pszName, &m_data);
            }

            ~init()
            {
                if (m_hFind != INVALID_HANDLE_VALUE)
                    ::FindClose(m_hFind)|verified;
            }
        };


        template<class = void>
        struct super_ :
            oven::iter_range<
                detail::find_file_iterator
            >
        { };


    } // namespace find_file_range_detail


    struct find_file_range  :
        private find_file_range_detail::init<>::type,
        find_file_range_detail::super_<>::type
    {
    private:
        typedef find_file_range_detail::init<>::type init_t;
        typedef find_file_range_detail::super_<>::type super_t;
        typedef super_t::iterator iter_t;

    public:
        template<class CStringizable>
        explicit find_file_range(CStringizable const& str) :
            init_t(str|c_str),
            super_t(iter_t(m_hFind, m_data), iter_t())
        { }

    private:
        find_file_range(find_file_range const&);
        find_file_range& operator=(find_file_range const&);
    };


} } // namespace pstade::gravy


#endif
