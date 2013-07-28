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
    
//    json_string obj("key", "value");
//    obj.write(std::cerr);
//    std::cerr << std::endl;
//
//    json_t<int> obj_i = make("key", 3);
//    //json_t<int> obj_i("key", 3);
//    obj_i.write(std::cerr);
//    std::cerr << std::endl;
//
//    json_t<double> obj_d = make("key", 3.1);
//    obj_d.write(std::cerr);
//    std::cerr << std::endl;
//
//    json_t<bool> obj_b = make("key", true);
//    obj_b.write(std::cerr);
//    std::cerr << std::endl;
//
//    json_t<const char*> obj_s = make("key", "value");
//    obj_s.write(std::cerr);
//    std::cerr << std::endl;
//
//    auto obj2 = make("root", make("key", false));
//    obj2.write(std::cerr);
//    std::cerr << std::endl;

    //any.
    jv o1(2);
    o1.write(std::cerr);
    std::cerr << std::endl;
    jv o2(false);
    o2.write(std::cerr);
    std::cerr << std::endl;

    jp p1("k1", o1);
    p1.write(std::cerr);
    std::cerr << std::endl;
//    p1.key = "k1";
//    p1.value = o1;

    jo obj1;
    obj1.jps = std::vector<jp>(1);
    obj1.write(std::cerr);
    std::cerr << std::endl;

    jv v3;
    v3 = o1;

    ja a1;
    std::vector<jv> jvs;
    jvs.push_back(o1);
    jvs.push_back(o2);
    a1.jvs = jvs;
    a1.write(std::cerr);
    std::cerr << std::endl;

    return 0;
}
