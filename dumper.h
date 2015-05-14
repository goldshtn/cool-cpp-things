#ifndef COOL_THINGS_DUMPER_H
#define COOL_THINGS_DUMPER_H

#include "namer.h"

#include <type_traits>
#include <string>
#include <iostream>

template <typename> using void_t = void;

template <typename, typename = void>
struct is_container : std::false_type
{
};

template <typename T>
struct is_container<T, void_t<typename T::iterator>> : std::true_type
{
};

template <>
struct is_container<std::string, void> : std::false_type
{
};

template <typename T>
void dump(std::ostream& os, T const&, bool = true); // forward declaration

template <typename T>
void dump_helper(std::ostream& os, T const& val, std::true_type)
{
    os << namer<T>::name() << " [";
    for (auto const& elem : val)
    {
        dump(os, elem, false);
        os << ", ";
    }
    os << "]";
}

template <typename T>
void dump_helper(std::ostream& os, T const& val, std::false_type)
{
    os << val;
}

template <typename T>
void dump(std::ostream& os, T const& val, bool newline)
{
    dump_helper(os, val, is_container<T>());
    if (newline)
        os << "\n";
}

#endif //COOL_THINGS_DUMPER_H
