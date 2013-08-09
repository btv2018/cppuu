

#include <string>
#include <tuple>
#include <utility>

//template<typename K, typename V>
//void write_json(const K& key, const V& value) {
//}

template<typename K, typename V>
void write_json(const std::pair<K, V>& pair) {
}

template<typename T>
void write_json(const T& tuple) {
}

template<typename T>
void write_value(T t) {
    
}

void write_iterable() {
}

template<typename K>
void write_key(K key) {
}

template<typename H>
void write_iterable(H head) {
    // write head
    write_value(head);
}

template<typename H, typename... T>
void write_iterable(H head, T... tail) {
    write_value(head);
    // write ,
    write_iterable(tail...);
}


template<typename... T>
void write_array(T... args) {
    // write [
    write_iterable(args...);
    // write ]
}

void write_pair_iterable() {
}

template<typename K, typename V>
void write_pair_iterable(std::pair<K, V> head) {
    write_key(head.first);
    // write :
    write_value(head.second);
}

template<typename K, typename V, typename... T>
void write_pair_iterable(std::pair<K, V> head, T... tail) {
    // write head
    write_pair_iterable(tail...);
    // write ,
}
// {{"k",1}, {"k", {1,2,3}}}

struct c {
    int i;
    std::string s;
};

c foo() {
    return {1, "sd"};
}

template<typename K, typename V>
std::pair<K, V> p(K key, V value) {
    return {key, value};
}

template<typename T>
void bar(std::pair<int, int> p) {
}

int main() {


   write_iterable('a', 3, std::string());

    write_pair_iterable<const char*, int>({"k", 2});
    
    write_pair_iterable(p("k", 2), p("sd", p("sd", 1)));

    c c_{1, "sd"};


   return 0;
}
