#ifndef __OSTREAM_OPERATORS_H_
#define __OSTREAM_OPERATORS_H_

#include <iostream>
#include <sstream>
#include <map>
#include <set>

#include <boost/mpl/has_xxx.hpp>
#include <boost/utility.hpp>

template<typename T>
void print_iterable(std::ostream& os, T arg) {
    typename T::const_iterator it = arg.begin();
    if (it != arg.end()) {
        os << *it;
        ++it;
    }
    for (; it != arg.end(); ++it) {
        os << ", " << *it;
    }
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& pair) {
    return os << "(" << pair.first << ", " << pair.second << ")";
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& map) {
    os << "{";
    print_iterable(os, map);
    return os << "}";
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& set) {
    os << "{";
    print_iterable(os, set);
    return os << "}";
}

BOOST_MPL_HAS_XXX_TRAIT_DEF(const_iterator)
BOOST_MPL_HAS_XXX_TRAIT_DEF(type_traits)

// for types with const_operator (std::vector, std::list, ...), but not for std::string
template<typename T>
typename boost::enable_if<has_const_iterator<T>, std::ostream&>::type
operator<<(
typename boost::disable_if<has_type_traits<T>, std::ostream&>::type os,
T t)
{
    os << "[";
    print_iterable(os, t);
    return os << "]";
}


template<typename T>
std::string to_string(T t) {
    std::ostringstream os;
    os << t;
    return os.str();
}


#endif // __OSTREAM_OPERATORS_H_
