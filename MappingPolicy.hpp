#include <thread>
#include <vector>

namespace PPT
{
    template <typename T>
    using v_iter = std::vector<T>::iterator;
    template <typename T>
    using v_citer = std::vector<T>::const_iterator;

    template <typename T, typename AccessPolicy>
    class CombinationMapping
    {
    public:
        CombinationMapping(int size, int n_threads)
            : input_a_(size),
              input_b_(size),
              output_(size),
              workers_(n_threads)
        {
            for (auto i = 0; i < n_threads; ++i)
            {
                auto worker = workers_[i];
                std::tie(worker.a_begin, worker.a_end, worker.stride)
                    = AccessPolicy(input_a_.begin(), i, size, n_threads);
                std::tie(worker.b_begin, worker.b_end, worker.stride)
                    = AccessPolicy(input_b_.begin(), i, size, n_threads);
                std::tie(worker.out_begin, worker.out_end, worker.stride)
                    = AccessPolicy(output_.begin(), i, size, n_threads);
            }
        }

        struct Worker
        {
            std::thread thread_{};
            v_citer<T> a_begin;
            v_citer<T> a_end;
            v_citer<T> b_begin;
            v_citer<T> b_end;
            v_iter<T>  out_begin;
            v_iter<T>  out_end;
            int        stride;
        };

    private:
        std::vector<T> input_a_{};
        std::vector<T> input_b_{};
        std::vector<T> output_{};
        std::vector<Worker> workers_{};
    };
} // namespace PPT