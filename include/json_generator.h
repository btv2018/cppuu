#include <cassert>
#include <string>
#include <vector>
#include <ostream>
#include <iostream>

#include <boost/any.hpp>

namespace cppuu { namespace json {

struct json_array;
struct json_object;

void write_array(std::ostream& os, const json_array* array);
void write_object(std::ostream& os, const json_object* object);

void write_json_string(std::ostream& os, const char* str) {
    os << '"';
    int i = 0;
    while (const char ch = str[i++]) {
        if (ch == '\\' || ch == '"') {
            os << '\\';
        }
        os << ch;
    }
    os << '"';
}

void write_json_string(std::ostream& os, const std::string* str) {
    // TODO: handle \0
    write_json_string(os, str->c_str());
}

class json_value {
    enum ValueType {
        NIL,
        BOOL,
        INT,
        DOUBLE,
        C_STRING,
        STRING,
        ARRAY,
        OBJECT,
    };
    ValueType type;
    boost::any value;

public:
    json_value() : type(NIL) {}
    json_value(std::nullptr_t) : type(NIL) {}
    json_value(bool v) : type(BOOL), value(v) {}
    json_value(int v) : type(INT), value(v) {}
    json_value(double v) : type(DOUBLE), value(v) {}
    json_value(const char* v) : type(C_STRING), value(v) {}
    //json_value(const std::string& v) : type(STRING), value(v) {}
    json_value(std::string&& v) : type(STRING), value(v) {}
    json_value(const json_array& v) : type(ARRAY), value(v) {}
    json_value(const json_object& v) : type(OBJECT), value(v) {}

    void write(std::ostream& os) const {
        switch (type) {
          case NIL: {
            os << "null";
            break;
          }
          case BOOL: {
            os << (boost::any_cast<bool>(value) ? "true" : "false");
            break;
          }
          case INT: {
            os << boost::any_cast<int>(value);
            break;
          }
          case DOUBLE: {
            os << boost::any_cast<double>(value);
            break;
          }
          case C_STRING: {
            write_json_string(os, boost::any_cast<const char*>(value));
            break;
          }
          case STRING: {
            write_json_string(os, boost::any_cast<std::string>(&value));
            break;
          }
          case ARRAY: {
            write_array(os, boost::any_cast<json_array>(&value));
            break;
          }
          case OBJECT: {
            write_object(os, boost::any_cast<json_object>(&value));
            break;
          }
          default: {
            assert(false);
          }
        }  
    }
};

class json_array {
    std::vector<json_value> values;

public:
    json_array() {}

    json_array(std::initializer_list<json_value> list) : values(list) {}

    void add_value(json_value&& value) {
        values.push_back(value);
    }

    void write(std::ostream& os) const {
        os << '[';
        auto it = begin(values);
        if (it != end(values)) {
            it->write(os);
            for (++it; it != end(values); ++it) {
                os << ", ";
                it->write(os);
            }
        }
        os << ']';
    }
};

class json_pair {
    const char* c_key;
    std::string key;
    json_value value;

public:
    json_pair() {}

    json_pair(std::string&& key, json_value&& value = nullptr)
      : c_key(0), key(key), value(value) {}
    
    json_pair(const char* key, json_value&& value = nullptr)
      : c_key(key), value(value) {}
    
    void write(std::ostream& os) const {
        if (c_key) {
            write_json_string(os, c_key);
        } else {
            write_json_string(os, &key);
        }
        os << ": ";
        value.write(os);
    }
};

class json_object {
    std::vector<json_pair> pairs;

public:
    json_object() {}

    json_object(std::initializer_list<json_pair> list) : pairs(list) {}

    json_object(json_pair&& pair) : pairs{pair} {}

    void add_member(json_pair&& pair) {
        pairs.push_back(pair);
    }

    void write(std::ostream& os) const {
        os << '{';
        auto it = begin(pairs);
        if (it != end(pairs)) {
            it->write(os);
            for (++it; it != end(pairs); ++it) {
                os << ", ";
                it->write(os);
            }
        }
        os << '}';
    }
};


void write_array(std::ostream& os, const json_array* array) {
    array->write(os);
}

void write_object(std::ostream& os, const json_object* object) {
    object->write(os);
}

std::string quote_json_string(const char* str) {
    std::string result("\"");
    return result.append(str).append("\"");
}

} } // namespace cppuu json

