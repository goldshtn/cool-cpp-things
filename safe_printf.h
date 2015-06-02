#ifndef COOL_THINGS_SAFE_PRINTF_H
#define COOL_THINGS_SAFE_PRINTF_H

#include <string>
#include <iostream>
#include <regex>

constexpr char FORMAT_SPECIFIER = '%';

struct constexpr_string
{
    unsigned size_;
    char const* string_;

    template <unsigned N>
    constexpr constexpr_string(char const(&str)[N])
            : size_(N), string_(str)
    {
    }

    constexpr unsigned count_format_specifiers() const
    {
        unsigned count = 0;
        for (auto i = 0; i < size_; ++i)
        {
            if (string_[i] == FORMAT_SPECIFIER)
            {
                if ((i != size_ - 1) && (string_[i+1] == FORMAT_SPECIFIER))
                    ++i; // skip next % as well, it was consumed by this one
                else
                    ++count;
            }
        }
        return count;
    }
};

unsigned count_format_specifiers(std::string const& format)
{
    unsigned count = 0;
    for (size_t i = 0; i < format.size(); ++i)
    {
        if (format[i] == FORMAT_SPECIFIER)
        {
            if ((i != format.size() - 1) && (format[i+1] == FORMAT_SPECIFIER))
                ++i; // skip next % as well, it was consumed by this one
            else
                ++count;
        }
    }
    return count;
}

std::string unquote_format_specifiers(std::string const& format)
{
    static std::regex double_specifier("%%");
    static std::string single_specifier("%");
    return std::regex_replace(format, double_specifier, single_specifier);
}

void safe_printf(std::string const& format)
{
    if (count_format_specifiers(format) != 0)
        throw std::invalid_argument("number of arguments doesn't match the format string");

    std::cout << unquote_format_specifiers(format);
}

template <typename Head, typename... Tail>
void safe_printf(std::string const& format, Head head, Tail... tail)
{
    if (count_format_specifiers(format) != sizeof...(Tail) + 1)
        throw std::invalid_argument("number of arguments doesn't match the format string");

    auto first_format_pos = format.find_first_of(FORMAT_SPECIFIER);
    std::cout << format.substr(0, first_format_pos);

    if (first_format_pos != format.size() - 1 && format[first_format_pos+1] == FORMAT_SPECIFIER)
        ++first_format_pos;

    std::cout << head;
    safe_printf(format.substr(first_format_pos+1), tail...);
}

template <typename... Types>
constexpr unsigned sizeof_args(Types...)
{
    return static_cast<unsigned int>(sizeof...(Types));
}

#define SAFE_PRINTF(format, ...) \
  static_assert(constexpr_string(format).count_format_specifiers() \
    == sizeof_args(__VA_ARGS__), \
    "number of arguments doesn't match the format string"); \
  safe_printf(format, ##__VA_ARGS__);

#endif //COOL_THINGS_SAFE_PRINTF_H
