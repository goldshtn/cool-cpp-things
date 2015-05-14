#ifndef COOL_THINGS_NAMER_H
#define COOL_THINGS_NAMER_H

#include <string>
#include <type_traits>
#include <vector>

template <typename T>
struct namer
{
    static std::string name() { return typeid(T).name(); }
};

template <>
struct namer<int>
{
    static std::string name() { return "int"; }
};

template <>
struct namer<std::string>
{
    static std::string name() { return "std::string"; }
};

// More declarations for other primitive types should follow

template <typename...>
struct typelist_to_namelist;

template <typename T>
struct typelist_to_namelist<T>
{
    static std::string namelist() { return namer<T>::name(); }
};

template <typename T, typename... Ts>
struct typelist_to_namelist<T, Ts...>
{
    static std::string namelist()
    {
        return typelist_to_namelist<T>::namelist() + ", " + typelist_to_namelist<Ts...>::namelist();
    }
};

template <typename... Ts>
struct namer<std::vector<Ts...>>
{
    static std::string name()
    {
        std::string name("std::vector<");
        name += typelist_to_namelist<Ts...>::namelist();
        return name + ">";
    }
};

template <typename... Ts>
struct namer<std::allocator<Ts...>>
{
    static std::string name() { return "std::allocator"; }
};

// More declarations for other containers should follow

#endif //COOL_THINGS_NAMER_H
