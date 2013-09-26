
#include "atlstr.h"


#define PSTADE_BISCUIT_DEBUG_OUT std::wcout
// �p�[�T�[�f�o�b�O�o��
#include <pstade/biscuit.hpp>

#include <pstade/oven.hpp>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/assign.hpp>
#include <boost/cstdint.hpp> // for uintXXX_t

#include <vector>

using namespace std;
using namespace pstade;
using namespace biscuit;


PSTADE_BISCUIT_SET_LITERAL(nengo, L"���N���������吳���a����")


struct headpattern :
    seq<
        sol,
        repeat<or_<wchrng<L'�O',L'�X'>, nengo>, 2>,
        plus< not_< wchset<L' ',L'�@',L'�i'> > >
    >
{ };


struct bb_action
{
    template< class SubRange >
        void operator()(SubRange rng, std::wostream& out)
    {
	    out <<"<B>"<<oven::copy_range<std::wstring>(rng)<<"</B>";
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
    locale::global(locale("japanese"));// windows ���{�� �O��S-JIS ���� wchar_t

    biscuit::iterate< actor<headpattern, bb_action> >(
        oven::make_istream_range(wcin)|oven::multi_passed,
        wcout, biscuit::output_action()
    );

    return 0;
}
