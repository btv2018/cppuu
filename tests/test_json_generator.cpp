#include <iostream>
#include <boost/any.hpp>

#include "json_generator.h"

#ifdef _DEBUG
#define DBG_PRINT(var) \
  std::cerr << "DBG: " << __FILE__ << ":" << __LINE__ << "\t"\
       << #var << ":\t" << (var) << std::endl
#else
#define DBG_PRINT(var)
#endif

using namespace cppuu::json;

int main() {

    //any.
    json_value v1(2);
    v1.write(std::cerr);
    std::cerr << std::endl;
    json_value v2(true);
    v2.write(std::cerr);
    std::cerr << std::endl;
    json_value v3("st\\ring");
    v3.write(std::cerr);
    std::cerr << std::endl;

    std::string str("fdsdf");
    json_value v4(std::move(str));
    v4.write(std::cerr);
    std::cerr << std::endl;

    json_pair p1("key");
    //json_pair p1("key", nullptr);
    p1.write(std::cerr);
    std::cerr << std::endl;

    json_array a1{1,2,true};
    a1.add_value(std::move(v1));
    a1.add_value("tipa");
    a1.add_value(nullptr);
    a1.add_value(0);
    a1.add_value(json_array());
    a1.write(std::cerr);
    std::cerr << std::endl;

    json_object o1({{"root", std::move(a1)}, {"s", "s"}});
    //json_object o1({p1});
    o1.add_member({"1", "2"});
    o1.write(std::cerr);
    std::cerr << std::endl;

    


///    jp p1("k1", o1);
///    p1.write(std::cerr);
///    std::cerr << std::endl;
///
///    json_objecto obj1;
///    obj1.jps = std::vector<jp>(1);
///    obj1.write(std::cerr);
///    std::cerr << std::endl;
///
///    jv v3;
///    v3 = o1;
///
///    ja a1;
///    std::vector<jv> jvs;
///    jvs.push_back(o1);
///    jvs.push_back(o2);
///    a1.jvs = jvs;
///    a1.write(std::cerr);
///    std::cerr << std::endl;

    return 0;
}
