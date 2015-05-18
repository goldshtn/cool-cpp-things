#ifndef COOL_THINGS_CONCURRENCY_H
#define COOL_THINGS_CONCURRENCY_H

#include <future>
#include <thread>
#include <vector>

// Fn is a function void(unsigned)
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

template <typename InputIterator, typename OutputIterator, typename Transformer>
OutputIterator parallel_transform(
        InputIterator first, InputIterator last,
        OutputIterator out, Transformer transformer
)
{
    static_assert(std::is_assignable<decltype(*out), decltype(transformer(*first))>::value,
                  "specified transformer doesn't produce a value that can be assigned to the output iterator");

    std::mutex mut;
    std::vector<std::future<void>> futures;
    while (first != last) {
        futures.push_back(std::async([=,&mut,&out] {
            auto result = transformer(*first);
            std::lock_guard<std::mutex> lock{mut};
            *out++ = result;
        }));
        ++first;
    }
    for (auto const& fut : futures)
        fut.wait();
    return out;
}

#endif //COOL_THINGS_CONCURRENCY_H
