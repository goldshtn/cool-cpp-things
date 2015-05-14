#ifndef COOL_THINGS_UNITS_H
#define COOL_THINGS_UNITS_H

#include <iostream>

namespace units
{

    template <int Mass, int Time, int Length>
    struct unit
    {
        double value_;

        unit(double v) : value_(v)
        { }

        double value() const
        { return value_; }
    };

    template <int M1, int T1, int L1>
    unit<M1, T1, L1> operator+(unit<M1, T1, L1> u1, unit<M1, T1, L1> u2)
    {
        return u1.value() + u2.value();
    }

    template <int M1, int T1, int L1>
    unit<M1, T1, L1> operator-(unit<M1, T1, L1> u1, unit<M1, T1, L1> u2)
    {
        return u1.value() - u2.value();
    }

    template <int M1, int T1, int L1, int M2, int T2, int L2>
    unit<M1 + M2, T1 + T2, L1 + L2> operator*(unit<M1, T1, L1> u1, unit<M2, T2, L2> u2)
    {
        return u1.value() * u2.value();
    }

    template <int M1, int T1, int L1, int M2, int T2, int L2>
    unit<M1 - M2, T1 - T2, L1 - L2> operator/(unit<M1, T1, L1> u1, unit<M2, T2, L2> u2)
    {
        return u1.value() / u2.value();
    }

    using scalar = unit<0, 0, 0>;
    using mass = unit<1, 0, 0>;
    using time = unit<0, 1, 0>;
    using distance = unit<0, 0, 1>;
    using speed = unit<0, -1, 1>; // meters per second
    using acceleration = unit<0, -2, 1>; // meters per second per second

    void symbol_sequence(std::ostream& os, std::initializer_list<std::pair<int, std::string>> seq)
    {
        bool first = true;
        for (auto const& p : seq)
        {
            if (p.first > 0)
            {
                if (!first)
                    os << " * ";
                os << p.second;
                if (p.first > 1)
                {
                    os << "^" << p.first;
                }
                first = false;
            }
        }
        first = true;
        for (auto const& p : seq)
        {
            if (p.first < 0)
            {
                if (first)
                    os << " / ";
                if (!first)
                    os << " * ";
                os << p.second;
                if (p.first < 1)
                {
                    os << "^" << -p.first;
                }
                first = false;
            }
        }
    }

    template <int M1, int T1, int L1>
    std::ostream& operator<<(std::ostream& os, unit<M1, T1, L1> u)
    {
        os << u.value() << " ";
        symbol_sequence(os, {{M1, "kg"},{T1, "s"},{L1,"m"}});
        return os;
    }

} // namespace units

#endif //COOL_THINGS_UNITS_H
