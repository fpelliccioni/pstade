#include <pstade/vodka/drink.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// UTF8�t�@�C������ɂȂ�܂������A
// Mingw�œ��{�ꂪ������悤�ɂȂ�܂����B


// Visual C++ 2005 Express Edition �́A
// ���{��̃p�X�̃t�@�C�����J���Ȃ��悤�ł��B


// �L�[���[�h�̃����N��L���ɂ���Ƃ���
// 'cpp_to_hatena::set_hatena_mode(false);'


#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/void.hpp>

#include <pstade/biscuit.hpp>
#include <pstade/oven.hpp>
#include <pstade/oven/tab_expanded.hpp>
#include <pstade/oven/utf8_decoded.hpp>
#include <pstade/oven/utf8_encoded.hpp>
#include <pstade/oven/utf8_encoder.hpp>
#include <pstade/wine.hpp>
#include "./start.hpp"
#include "./hatena_mode.hpp"


// �^�u�T�C�Y���J�X�^�}�C�Y���Ă�������
//
template< class = void >
struct tabsize :
    boost::mpl::int_<4>
{ };


struct newline_cvter
{
    typedef boost::uint32_t result_type;

    template< class SubRange >
    boost::uint32_t operator()(SubRange rng) const
    {
        using namespace pstade;
        if (biscuit::match<biscuit::wnewline>(rng)) {
            return '\n';
        }
        else {
            if (pstade::oven::distance(rng) == 0)
                BOOST_ASSERT(false);
            BOOST_ASSERT(pstade::oven::distance(rng) == 1);
            return *boost::begin(rng);
        }
    }
};


int main(int argc, char *argv[])
{
    using namespace pstade;
    using namespace biscuit;

    // cpp_to_hatena::set_hatena_mode(false);

    std::cout << "<cpp_to_hatena>";

    BOOST_FOREACH (int i, oven::counting(1, argc)) {

        try {
            std::string iname(argv[i]);
            std::cout << "<input-file>" << iname << "</input-file>";

            std::string oname = iname + ".xml";
            std::ofstream fout(oname.c_str(), std::ios::binary);
            pstade::require(fout, "good output file: " + oname);

            oven::copy("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>"
                "<pre class=\"cpp_source\">"|oven::as_literal, oven::stream_writer(fout));

            biscuit::match<
                iteration<cpp_to_hatena::start, cpp_to_hatena::act_line_escape>
            >(
                oven::file_range<boost::uint8_t>(iname)                  // spirit::file_iterator�̃y�A
                    | pstade::required("non-empty input file: " + iname) // ���Range�͗�O��
                    | oven::utf8_decoded                                 // UTF-8��UTF-32�ɕϊ�
                    | biscuit::tokenized< or_<wnewline, any> >()         // ���s�Ƃ����łȂ����̂ɕ�����
                    | oven::transformed(::newline_cvter())               // ���s�Ȃ�'\n'�ɕϊ�����
                    | oven::tab_expanded(::tabsize<>::value)             // �^�u���󔒂ɂ���
                    | oven::memoized,                                    // �������邽�߃L���b�V������
                oven::utf8_encoder |= oven::stream_writer(fout)          // UTF-8�ɖ߂��ďo��
            );

            oven::copy("</pre>"|oven::as_literal, oven::stream_writer(fout));

            std::cout << "<output-file>" << oname << "</output-file>";

        }
        catch (std::exception& err) {
            std::cout << "<error>" << err.what() << "</error>\n";
            return 0; // continue;
        }

    } // BOOST_FOREACH

    return std::cout << "</cpp_to_hatena><press-any-key/>", pstade::pause();
}
