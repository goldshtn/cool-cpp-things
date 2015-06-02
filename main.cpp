#include "safe_printf.h"
#include "dumper.h"
#include "concurrency.h"
#include "units.h"
#include "evector.h"

#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std::string_literals;

// Safe printf
void cool_thing_1()
{
    SAFE_PRINTF("today is June %\n", 2);
    SAFE_PRINTF("my stocks went down 3%% today\n");

    // Shouldn't compile
//    SAFE_PRINTF("today is June %\n");
//    SAFE_PRINTF("my stocks went down 3%% today\n", 3);
}

// Container dumper
void cool_thing_2()
{
    static_assert(is_container<std::vector<int>>::value, "vector<int>");
    static_assert(!is_container<std::string>::value, "string");
    static_assert(!is_container<int>::value, "int");
    static_assert(is_container<std::vector<std::vector<int>>>::value, "vector<vector<int>>");

    dump(std::cout, "Hello"s);
    dump(std::cout, std::vector<int>{1,2,3});
    dump(std::cout, 42);
    dump(std::cout, std::vector<std::vector<int>>{{1,2,3},{4,5,6}});
}

// Units (dimensional analysis)
void cool_thing_3()
{
    using namespace units;

    speed sp = 60.0_m / 1.0_s;
    distance distance_traveled = sp * 5.0_s;
    std::cout << "distance = " << distance_traveled << "\n";

    acceleration accel = (9.8_m / 1.0_s) / 1.0_s;
    std::cout << "g ~~ " << accel << "\n";
}

// Expression templates
void cool_thing_4()
{
    vec u{1, 2, 3, 4, 5};
    vec v{2, 3, 4, 5, 6};
    vec w{0, 1, 0, 1, 0};
    vec r = 2*u - (v + w);
    std::cout << r << "\n";
};

int main()
{
    cool_thing_1();
//    cool_thing_2();
//    cool_thing_3();
//    cool_thing_4();

    return 0;
}