#ifndef PSTADE_PIZZA_INI_SECTION_HPP
#define PSTADE_PIZZA_INI_SECTION_HPP


// PStade.Pizza
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// MFC7::CWinApp::WriteProfileXXX


#if !defined(_WIN32_WCE)


#include <cstddef> // size_t
#include <boost/assert.hpp>
#include <boost/mpl/int.hpp>
#include <boost/range/empty.hpp>
#include <pstade/egg/integralize.hpp>
#include <pstade/gravy/c_str.hpp>
#include <pstade/gravy/module_file_name.hpp>
#include <pstade/gravy/tstring.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/instance.hpp>
#include <pstade/oven/array_range.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/copied.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/equals.hpp>
#include <pstade/require.hpp>


namespace pstade { namespace pizza {


namespace ini_section_detail {


    PSTADE_INSTANCE((gravy::tstring) const,
        magicStr, (_T("pstade_tomato_ini_section_detail_magic_string"))
    )


    inline
    bool query_string(const TCHAR* pszFileName, const TCHAR* pszSectionName,
        TCHAR const *pszValueName, TCHAR *pFirst, TCHAR *pLast)
    {
        {
            // empty-string also is valid value, so we must go...

            oven::array_range<TCHAR> buf(1 + oven::distance(magicStr));

            ::GetPrivateProfileString(
                pszSectionName, pszValueName,
                gravy::c_str(magicStr), // default
                boost::begin(buf), oven::distance(buf)|egg::integralize(),
                pszFileName);

            if (oven::equals(buf|oven::as_c_str, magicStr))
                return false;
        }

        ::GetPrivateProfileString( // bufsz contains NULL (== buffer size) >= 1
            pszSectionName, pszValueName,
            _T(""), pFirst, (pLast - pFirst)|egg::integralize(), pszFileName);

        return true;
    }


} // namespace ini_section_detail


struct ini_section
{
    ini_section()
    { }

    template< class CStringizeable0, class CStringizeable1 >
    ini_section(const CStringizeable0& fileName, const CStringizeable1& sectionName)
    {
        open(fileName, sectionName);
    }

    template< class CStringizeable0, class CStringizeable1 >
    void open(const CStringizeable0& fileName, const CStringizeable1& sectionName)
    {
        m_fileName = gravy::c_str(fileName);
        m_sectionName = gravy::c_str(sectionName);

        BOOST_ASSERT(oven::distance(m_fileName) < 4095); // can't read in bigger
    }

    void close()
    {
        m_fileName.clear();
        m_sectionName.clear();
    }


    gravy::tstring get_file_name() const
    { return m_fileName; }

    gravy::tstring get_section_name() const
    { return m_sectionName; }

    bool is_open() const
    { return !boost::empty(m_fileName) && !boost::empty(m_sectionName); }


typedef ini_section pstade_pizza_profile;
    void pstade_pizza_initialize(TCHAR const *pszName)
    {
        gravy::module_file_name mf;
        gravy::tstring ini = mf.identifier()|oven::copied;
        ini += _T(".ini");
        open(ini, pszName);
    }

    void pstade_pizza_set_string(TCHAR const *pszValueName, TCHAR const *pszValue)
    {
        // Note: if pszValue is NULL, section is deleted.
        BOOST_ASSERT(is_open());
        BOOST_ASSERT(!oven::equals(pszValue|oven::as_c_str, ini_section_detail::magicStr));

        PSTADE_REQUIRE(
            ::WritePrivateProfileString(
                gravy::c_str(m_sectionName), pszValueName,
                pszValue, gravy::c_str(m_fileName))
        );
    }

    bool pstade_pizza_query_string(TCHAR const *pszValueName, TCHAR *pFirst, TCHAR *pLast)
    {
        BOOST_ASSERT(is_open());

        return ini_section_detail::query_string(
            gravy::c_str(m_fileName), gravy::c_str(m_sectionName),
            pszValueName, pFirst, pLast);
    }

    bool pstade_pizza_delete(TCHAR const *pszValueName)
    {
        BOOST_ASSERT(is_open());

        PSTADE_REQUIRE(
            ::WritePrivateProfileString(
                gravy::c_str(m_sectionName), pszValueName, NULL, gravy::c_str(m_fileName))
        );
    }

private:
    gravy::tstring m_fileName, m_sectionName;
};


template< class CStringizeable0, class CStringizeable1 > inline
void delete_ini_section(const CStringizeable0& fileName, const CStringizeable1& sectionName)
{
    PSTADE_REQUIRE(
        ::WritePrivateProfileString(gravy::c_str(sectionName), NULL, NULL, gravy::c_str(fileName))
    );
}


} } // namespace pstade::pizza


#endif // !defined(_WIN32_WCE)


#endif
