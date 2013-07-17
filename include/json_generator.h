#include <string>
#include <ostream>
#include <iostream>

namespace cppuu { namespace json {

std::string quote_json_string(const char* str) {
    std::string result("\"");
    return result.append(str).append("\"");
}


template<typename T>
void write_value(std::ostream& os, T value) {
    os << value;
}

template<>
void write_value<bool>(std::ostream& os, bool value) {
    if (value) {
        os << "true";
    } else {
        os << "false";
    }
}


template<>
void write_value<const char*>(std::ostream& os, const char* value) {
    os << quote_json_string(value);
}


template<typename T>
class json_t {
    const char* key;
    const T value;

public:
    json_t(const char* key, const T& value) : key(key), value(value) {}

    void write(std::ostream& os) const {
        os << '{' << quote_json_string(key) << ':';
        write_value(os, value);
        os << '}';
    }
};

template<typename T>
void write_value(std::ostream& os, const json_t<T>& value) {
//    os << '{';
    value.write(os);
//    os << '}';
}



template<typename T>
json_t<T> make(const char* key, T value) {
    return json_t<T>(key, value);
}


// ---------------------------------------------------------------------------
class json {
    const std::string key;

public:
    json(const std::string& key) : key(key) {}

    virtual ~json() {}

    void write(std::ostream& os) {
//        os << '{' << quote_json_string(key) << ':';
        write_value(os);
        os << '}';
    }

    virtual void write_value(std::ostream& os) const = 0;
};

class json_string : public json {
    const std::string value;

public:
    json_string(const std::string& key, const std::string& value)
        : json(key), value(value) {}

    virtual void write_value(std::ostream& os) const {
 //       os << quote_json_string(value);
    }
};


} } // namespace cppuu json

