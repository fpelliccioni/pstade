
#include <boost/fusion/include/find.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/boost_tuple.hpp>
#include <boost/fusion/include/count.hpp>


int main()
{
    {
        boost::fusion::vector<> v;
        boost::fusion::begin(v);
        boost::fusion::find<int>(v);
        boost::fusion::count(v, 1);
    }
    {
        boost::tuples::tuple<> t;
        boost::fusion::begin(t);
        //boost::fusion::count(t, 1); // doesn't compile.
        //boost::fusion::find<int>(t);// doesn't compile.
    }
}


