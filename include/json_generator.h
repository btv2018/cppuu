#include <string>
#include <vector>
#include <ostream>
#include <iostream>

#include <boost/any.hpp>

namespace cppuu { namespace json {

struct ja;
struct jo;

void write_a(std::ostream& os, const ja* a);
void write_o(std::ostream& os, const jo* o);

struct jv {
    enum ValueType {
        NIL,
        BOOL,
        INT,
        STRING,
        ARRAY,
        OBJECT,
    };
    ValueType type;

    boost::any value;
    jv() : type(NIL) {}
    jv(int v) : value(v), type(INT) {}
    jv(bool v) : value(v), type(BOOL) {}
    jv(const std::string& v) : value(v), type(STRING) {}
    jv(const ja& v) : value(v), type(ARRAY) {}
    jv(const jo& v) : value(v), type(OBJECT) {}
    void write(std::ostream& os) const {
        if (type == NIL) {
            os << "null";
        } else if (type == BOOL) {
            bool v = boost::any_cast<bool>(value);
            os << (true ? "true" : "false");
        } else if (type == INT) {
            os << boost::any_cast<int>(value);
        } else if (type == STRING) {
            os << *boost::any_cast<std::string>(&value);
        } else if (type == ARRAY) {
            write_a(os, boost::any_cast<ja>(&value));
        } else if (type == OBJECT) {
            write_o(os, boost::any_cast<jo>(&value));
        }
    }
};

struct ja {
    std::vector<jv> jvs;
    void write(std::ostream& os) const {
        os << '[';
        for (auto it = begin(jvs); it != end(jvs); ++it) {
            os << ", ";
            it->write(os);
        }
        os << ']';
    }
};

struct jp {
    std::string key;
    jv value;
    jp() {}
    jp(const std::string& key, const jv& value) : key(key), value(value) {}
    void write(std::ostream& os) const {
        os << key << ": ";
        value.write(os);
    }
};

struct jo {
    std::vector<jp> jps;
    void write(std::ostream& os) const {
        os << '{';
        for (auto it = begin(jps); it != end(jps); ++it) {
            os << ", ";
            it->write(os);
        }
        os << '}';
    }
};


void write_a(std::ostream& os, const ja* a) {
    a->write(os);
}

void write_o(std::ostream& os, const jo* o) {
    o->write(os);
}

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

