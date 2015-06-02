#ifndef COOL_THINGS_DUMPER_H
#define COOL_THINGS_DUMPER_H

#include "namer.h"

#include <type_traits>
#include <string>
#include <iostream>

template <typename> using void_t = void;

// The base case -- an arbitrary type is not a container
template <typename, typename = void>
struct is_container
        : std::false_type
{
};

// Specialization -- a type is a container if it has an inner
// typedef called 'iterator'
template <typename T>
struct is_container<T, void_t<typename T::iterator>>
        : std::true_type
{
};

// Specialization for strings, which we don't treat as containers
template <>
struct is_container<std::string, void>
        : std::false_type
{
};

template <typename T>
void dump(std::ostream&, T const&, bool = true); // forward declaration

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
