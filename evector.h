#ifndef COOL_THINGS_EVECTOR_H
#define COOL_THINGS_EVECTOR_H

#include <stddef.h>
#include <cassert>
#include <vector>
#include <iostream>

template <typename E>
class vec_expression
{
public:
    auto size() const
    { return static_cast<E const&>(*this).size(); }

    auto operator[](size_t i) const
    { return static_cast<E const&>(*this)[i]; }

    explicit operator E&()
    { return static_cast<      E&>(*this); }

    explicit operator E const&() const
    { return static_cast<const E&>(*this); }
};

class vec : public vec_expression<vec>
{
    std::vector<double> data_;
public:
    auto  operator[](size_t i)
    { return data_[i]; }

    auto operator[](size_t i) const
    { return data_[i]; }

    auto size() const
    { return data_.size(); }

    explicit vec(size_t n) : data_(n)
    { }

    explicit vec(std::initializer_list<double> elements) : data_(elements)
    { }

    template <typename E>
    vec(vec_expression<E> const& vec)
    {
        E const& v = static_cast<E const&>(vec);
        data_.resize(v.size());
        for (size_t i = 0; i != v.size(); ++i)
        {
            data_[i] = v[i];
        }
    }
};

std::ostream& operator<<(std::ostream& os, vec const& v)
{
    os << "[ ";
    for (size_t i = 0; i < v.size(); ++i)
        os << v[i] << " ";
    os << "]";
    return os;
}

template <typename E1, typename E2>
class vec_difference : public vec_expression<vec_difference<E1, E2>>
{
    E1 const& u_;
    E2 const& v_;
public:
    vec_difference(vec_expression<E1> const& u, vec_expression<E2> const& v) : u_(u), v_(v)
    {
        assert(u.size() == v.size());
    }

    auto size() const
    { return v_.size(); }

    auto operator[](size_t i) const
    { return u_[i] - v_[i]; }
};

template <typename E1, typename E2>
class vec_sum : public vec_expression<vec_sum<E1, E2>>
{
    E1 const& u_;
    E2 const& v_;
public:
    vec_sum(vec_expression<E1> const& u, vec_expression<E2> const& v) : u_(u), v_(v)
    {
        assert(u.size() == v.size());
    }

    auto size() const
    { return v_.size(); }

    auto operator[](size_t i) const
    { return u_[i] + v_[i]; }
};

template <typename E>
class vec_scaled : public vec_expression<vec_scaled<E>>
{
    double alpha_;
    E const& v_;
public:
    vec_scaled(double alpha, vec_expression<E> const& v) : alpha_(alpha), v_(v)
    { }

    auto size() const
    { return v_.size(); }

    auto operator[](size_t i) const
    { return alpha_ * v_[i]; }
};

template <typename E1, typename E2>
vec_difference<E1, E2> const
operator-(vec_expression<E1> const& u, vec_expression<E2> const& v)
{
    return vec_difference<E1, E2>(u, v);
}

template <typename E1, typename E2>
vec_sum<E1, E2> const
operator+(vec_expression<E1> const& u, vec_expression<E2> const& v)
{
    return vec_sum<E1, E2>(u, v);
}

template <typename E>
vec_scaled<E> const
operator*(double alpha, vec_expression<E> const& v)
{
    return vec_scaled<E>(alpha, v);
}

#endif //COOL_THINGS_EVECTOR_H
