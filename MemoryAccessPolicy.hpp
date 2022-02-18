#include <tuple>

namespace PPT
{
    template <typename Iter>
    class ContiguousAccess
    {
    public:
        auto operator()(Iter start, int thread_id, int array_size, int n_threads)
            -> std::tuple<int, int, int>
        {
            auto entries_per_thread = (array_size + n_threads - 1) / n_threads;
            auto begin_index = thread_id * entries_per_thread;
            auto stride      = 1;
            auto end_index   = begin_index + stride * entries_per_thread;
            return std::make_tuple(start + begin_index, start + end_index, stride);
        }
    };

    template <typename Iter>
    class InterleavedAccess
    {
    public:
        auto operator()(Iter start, int thread_id, int array_size, int n_threads)
            -> std::tuple<int, int, int>
        {
            auto entries_per_thread = (array_size + n_threads - 1) / n_threads;
            auto begin_index = thread_id;
            auto stride      = n_threads;
            auto end_index   = begin_index + stride * entries_per_thread;
            return std::make_tuple(start + begin_index, start + end_index, stride);
        }
    };
} // namespace PPT