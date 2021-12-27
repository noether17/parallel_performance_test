#include "AlgorithmTester.hpp"

namespace AT
{
auto element_wise_addition(std::vector<data_type>& output_vector,
                           const std::vector<data_type>& input_vector,
                           int thread_begin,
                           int thread_end,
                           int stride)
{
    for (int i = thread_begin; i < thread_end; i += stride)
    {
        output_vector[i] += input_vector[i];
    }
}

auto element_wise_multiplication(std::vector<data_type>& output_vector,
                                 const std::vector<data_type>& input_vector,
                                 int thread_begin,
                                 int thread_end,
                                 int stride)
{
    for (int i = thread_begin; i < thread_end; i += stride)
    {
        output_vector[i] *= input_vector[i];
    }
}

auto parse_algorithm(Algorithm alg)
    -> void(*)(std::vector<data_type>&,
               const std::vector<data_type>&,
               int,
               int,
               int)
{
    switch (alg)
    {
        case Algorithm::element_wise_addition:
            return element_wise_addition;
        case Algorithm::element_wise_multiplication:
            return element_wise_multiplication;
    }
}

/* Returns tuple containing thread offset,
 * stride between successive elements, and
 * length of thread segment.
 */
auto offset_stride_length(int array_size,
                          int parallelism,
                          MemoryAccess access)
                          -> std::tuple<int, int, int>
{
    auto max_ops_per_thread = (array_size + parallelism - 1) / parallelism;
    if (access == MemoryAccess::interleaved)
    {
        return make_tuple(1, parallelism, parallelism*max_ops_per_thread);
    }
    return make_tuple(max_ops_per_thread, 1, max_ops_per_thread);
}

auto test_performance(Algorithm alg,
                      int array_size,
                      int parallelism,
                      Hardware processor = Hardware::CPU,
                      MemoryAccess access = MemoryAccess::contiguous,
                      int block_size = default_block_size) -> ns
{
    // TODO
    // Need function to parse Algorithm and return function pointer
    //   --may also return number of inputs needed
    // Then generate input vector(s)
    // Different threads need a reference to same vectors(s) and
    //   a thread offset / stride

    // Start with CPU implementation for element-wise operations
    // Determine algorithm
    //auto func = parse_algorithm(alg);
    auto func = element_wise_addition; // start with getting this to work

    // create data vectors
    auto input_vector = std::vector<data_type>(array_size);
    std::iota(input_vector.begin(), input_vector.end(), 1);
    auto output_vector = std::vector<data_type>(array_size);
    std::iota(output_vector.begin(), output_vector.end(), 1);

    // create vector of threads
    auto threads = std::vector<std::thread>(parallelism);

    // set boundary parameters
    auto [thread_offset, stride, thread_length]
        = offset_stride_length(array_size, parallelism, access);
    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    // start threads
    for (int thread_index = 0; thread_index < threads.size(); ++thread_index)
    {
        // set thread boundaries
        auto thread_begin = thread_offset*thread_index;
        auto thread_end   = min(array_size, thread_begin + thread_length);
        threads[thread_index] = std::thread{func,
                                            std::ref(output_vector),
                                            std::cref(input_vector),
                                            thread_begin,
                                            thread_end,
                                            stride};
    }
    // join threads
    for (auto thread& : threads)
    {
        thread.join();
    }
    // end timer
    auto end = std::chrono::high_resolution_clock::now();

    // return execution time
    return end - start;
}
} // namespace AT