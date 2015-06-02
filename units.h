#ifndef COOL_THINGS_UNITS_H
#define COOL_THINGS_UNITS_H

#include <iostream>

#include "intvector.h"

namespace units
{

    template <typename IntVector>
    struct unit
    {
        double value_;

        unit(double v) : value_(v)
        { }

        double value() const
        { return value_; }
    };

    template <typename IntVector>
    unit<IntVector> operator+(unit<IntVector> u1, unit<IntVector> u2)
    {
        return u1.value() + u2.value();
    }

    template <typename IntVector>
    unit<IntVector> operator-(unit<IntVector> u1, unit<IntVector> u2)
    {
        return u1.value() - u2.value();
    }

    template <typename IntVector1, typename IntVector2>
    unit<typename intvector_add<IntVector1, IntVector2>::type>
    operator*(
            unit<IntVector1> u1,
            unit<IntVector2> u2)
    {
        return u1.value() * u2.value();
    }

    template <typename IntVector1, typename IntVector2>
    unit<typename intvector_subtract<IntVector1, IntVector2>::type>
    operator/(
            unit<IntVector1> u1,
            unit<IntVector2> u2)
    {
        return u1.value() / u2.value();
    }

    template <int Mass, int Time, int Length>
    using system = intvector<Mass, Time, Length>;

    using scalar = unit<system<0, 0, 0>>;
    using mass = unit<system<1, 0, 0>>;
    using time = unit<system<0, 1, 0>>;
    using distance = unit<system<0, 0, 1>>;
    using speed = unit<system<0, -1, 1>>; // meters per second
    using acceleration = unit<system<0, -2, 1>>; // meters per second per second

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

    template <int Mass, int Time, int Length>
    std::ostream& operator<<(std::ostream& os, unit<system<Mass, Time, Length>> u)
    {
        os << u.value() << " ";
        symbol_sequence(os, {{Mass, "kg"},{Time, "s"},{Length,"m"}});
        return os;
    }

    inline namespace literals
    {
        mass operator "" _kg(long double kg)
        {
            return mass(kg);
        }
        distance operator "" _m(long double m)
        {
            return distance(m);
        }
        time operator "" _s(long double s)
        {
            return time(s);
        }
    }

} // namespace units

#endif //COOL_THINGS_UNITS_H
