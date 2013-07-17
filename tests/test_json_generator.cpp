#include <iostream>

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
    
    json_string obj("key", "value");
    obj.write(std::cerr);
    std::cerr << std::endl;

    json_t<int> obj_i = make("key", 3);
    //json_t<int> obj_i("key", 3);
    obj_i.write(std::cerr);
    std::cerr << std::endl;

    json_t<double> obj_d = make("key", 3.1);
    obj_d.write(std::cerr);
    std::cerr << std::endl;

    json_t<bool> obj_b = make("key", true);
    obj_b.write(std::cerr);
    std::cerr << std::endl;

    json_t<const char*> obj_s = make("key", "value");
    obj_s.write(std::cerr);
    std::cerr << std::endl;

    auto obj2 = make("root", make("key", false));
    obj2.write(std::cerr);
    std::cerr << std::endl;

    return 0;
}
