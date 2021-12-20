#include "AlgorithmTester.hpp"

namespace AT
{
auto element_wise_addition(std::vector<data_type>& output_vector,
                           const std::vector<data_type>& input_vector,
                           int thread_start,
                           int stride)
{
    for (int i = thread_start; i < input_vector.size(); i += stride)
    {
        output_vector[i] += input_vector[i];
    }
}

auto element_wise_multiplication(std::vector<data_type>& output_vector,
                                 const std::vector<data_type>& input_vector,
                                 int thread_start,
                                 int stride)
{
    for (int i = thread_start; i < input_vector.size(); i += stride)
    {
        output_vector[i] *= input_vector[i];
    }
}

auto parse_algorithm(Algorithm alg)
    -> void(*)(std::vector<data_type>&,
               const std::vector<data_type>&,
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

    // set thread boundary parameters
    auto thread_offset = array_size / parallelism; // depends on access
    auto stride = 1; // depends on access

    // start timer
    auto start = std::chrono::high_resolution_clock::now();
    // start threads
    for (int thread_index = 0; thread_index < threads.size(); ++thread_index)
    {
        threads[thread_index] = std::thread{func,
                                            std::ref(output_vector),
                                            std::cref(input_vector),
                                            thread_offset*thread_index,
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