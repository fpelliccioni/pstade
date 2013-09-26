#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <utility>
#include <pstade/object_generator.hpp>


using namespace pstade;


typedef
    object_generator< std::pair< deduce<_1, as_value>, deduce<_2, as_value> > >
T_make_pair;

T_make_pair const make_pair = T_make_pair();


void test()
{
    std::pair<int, char> p = ::make_pair(1, '2');
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
