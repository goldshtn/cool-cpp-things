#ifndef COOL_THINGS_INTVECTOR_H
#define COOL_THINGS_INTVECTOR_H

template <int... Ints>
struct intvector
{
    using type = intvector<Ints...>;
    static constexpr int length = sizeof...(Ints);
};

constexpr bool intvector_equal(intvector<>, intvector<>)
{
    return true;
}

template <int Int1, int... Ints1, int Int2, int... Ints2>
constexpr bool intvector_equal(intvector<Int1, Ints1...>, intvector<Int2, Ints2...>)
{
    static_assert(sizeof...(Ints1) == sizeof...(Ints2), "vector lengths must be equal");
    return (Int1 == Int2) && intvector_equal(intvector<Ints1...>(), intvector<Ints2...>());
}

template <int, typename>
struct intvector_prepend;

template <int Int, int... Ints>
struct intvector_prepend<Int, intvector<Ints...>>
{
    using type = intvector<Int, Ints...>;
};

template <typename...>
struct intvector_add;

template <>
struct intvector_add<intvector<>, intvector<>>
{
    using type = intvector<>;
};

template <int Int1, int... Ints1, int Int2, int... Ints2>
struct intvector_add<intvector<Int1, Ints1...>, intvector<Int2, Ints2...>>
{
    static_assert(sizeof...(Ints1) == sizeof...(Ints2), "vector lengths must be equal");
    using type = typename intvector_prepend<
            Int1 + Int2,
            typename intvector_add<intvector<Ints1...>, intvector<Ints2...>>::type
    >::type;
};

template <typename...>
struct intvector_subtract;

template <>
struct intvector_subtract<intvector<>, intvector<>>
{
    using type = intvector<>;
};

template <int Int1, int... Ints1, int Int2, int... Ints2>
struct intvector_subtract<intvector<Int1, Ints1...>, intvector<Int2, Ints2...>>
{
    static_assert(sizeof...(Ints1) == sizeof...(Ints2), "vector lengths must be equal");
    using type = typename intvector_prepend<
            Int1 - Int2,
            typename intvector_subtract<intvector<Ints1...>, intvector<Ints2...>>::type
    >::type;
};

void intvector_tests()
{
    static_assert(intvector_equal(intvector<>(), intvector<>()), "");
    static_assert(intvector_equal(intvector<1, 2>(), intvector<1, 2>()), "");

    using v = intvector<1, 2, 3>;
    using u = intvector<0, -1, 2>;
    using sum = typename intvector_add<u, v>::type;
    using diff = typename intvector_subtract<u, v>::type;
    static_assert(intvector_equal(sum(), intvector<1, 1, 5>()), "");
    static_assert(intvector_equal(diff(), intvector<-1, -3, -1>()), "");
}

#endif //COOL_THINGS_INTVECTOR_H
