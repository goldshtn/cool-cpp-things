#ifndef COOL_THINGS_CONCURRENCY_H
#define COOL_THINGS_CONCURRENCY_H

#include <future>
#include <thread>
#include <vector>

template <typename Fn>
void parallel_for(unsigned from, unsigned to, Fn&& fn)
{
    std::vector<std::future<void>> futures;
    futures.reserve(to - from);
    for (auto i = from; i < to; ++i)
    {
        futures.push_back(std::async(std::forward<Fn>(fn), i));
    }
    for (auto const& fut : futures)
    {
        fut.wait();
    }
}

void parallel_invoke()
{
}

template <typename Fn, typename... Fns>
void parallel_invoke(Fn&& fn, Fns&&... fns)
{
    auto fut = std::async(std::forward<Fn>(fn));
    parallel_invoke(std::forward<Fns>(fns)...);
    fut.wait();
}

#endif //COOL_THINGS_CONCURRENCY_H
