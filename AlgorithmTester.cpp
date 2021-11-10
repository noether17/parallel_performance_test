#include "AlgorithmTester.hpp"

namespace AT
{
auto parse_algorithm(Algorithm alg)
    -> void(*)(std::vector<data_type>&,
               const std::vector<data_type>&,
               int,
               int)
{
    switch (alg)
    {
        case Algorithm::element_wise_addition:
            return []
                (std::vector<data_type>& output_vector,
                 const std::vector<data_type>& input_vector,
                 int thread_start,
                 int stride)
                 {
                     for (int i = thread_start; i < input_vector.size(); i += stride)
                     {
                         output_vector[i] = input_vector[i] + input_vector[i];
                     }
                 }
        case Algorithm::element_wise_multiplication:
            return []
                (std::vector<data_type>& output_vector,
                 const std::vector<data_type>& input_vector,
                 int thread_start,
                 int stride)
                 {
                     for (int i = thread_start; i < input_vector.size(); i += stride)
                     {
                         output_vector[i] = input_vector[i] * input_vector[i];
                     }
                 }
    }
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
    auto func = parse_algorithm(alg);

    // create input vector(s)
    auto input_vector = std::vector<data_type>(array_size);
    std::iota(input_vector.begin(), input_vector.end(), 1);

    // create output vector
    auto output_vector = std::vector<data_type>(array_size);

    // create vector of threads
    auto threads = std::vector<std::thread>(parallelism);

    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    // start threads
    auto thread_index = 0;
    auto thread_offset = array_size / parallelism; // depends on access
    auto stride = 1; // depends on access
    for (const auto thread& : threads)
    {
        thread = std::thread{func,
                             std::ref(output_vector),
                             std::cref(input_vector),
                             thread_offset*thread_index++,
                             stride};
    }
    // join threads
    for (const auto thread& : threads)
    {
        thread.join();
    }
    // end timer
    auto end = std::chrono::high_resolution_clock::now();

    // return execution time
    return end - start;
}
} // namespace AT