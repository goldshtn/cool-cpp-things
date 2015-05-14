#include "safe_printf.h"
#include "dumper.h"
#include "concurrency.h"
#include "units.h"

#include <vector>
#include <string>
#include <random>
#include <chrono>

using namespace std::string_literals;

void cool_thing_1()
{
    SAFE_PRINTF("today is June %\n", 3);
    SAFE_PRINTF("my stocks went down 3%% today\n");

    // Shouldn't compile
//    SAFE_PRINTF("today is June %\n");
//    SAFE_PRINTF("my stocks went down 3%% today\n", 3);
}

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

void cool_thing_3()
{
    std::mt19937 rand;
    std::uniform_int_distribution<int> dist(10, 100);
    parallel_for(1, 100, [&](auto i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(dist(rand)));
        std::cout << i << " ";
    });
    std::cout << "\n";
}

void cool_thing_4()
{
    units::distance distance_traveled = units::speed(60.0) * units::time(5.0);
    std::cout << "distance = " << distance_traveled << "\n";

    units::acceleration accel = units::speed(9.8) / units::time(1.0);
    std::cout << "g ~~ " << accel << "\n";
}

int main()
{
    cool_thing_1();
    cool_thing_2();
    cool_thing_3();
    cool_thing_4();

    return 0;
}