#pragma once

#include <chrono>
#include <numeric>
#include <thread>
#include <vector>

namespace AT
{
constexpr auto default_block_size = 32; // warp consists of 32 threads
using ns = std::chrono::nanoseconds;
using data_type = int;

enum class Algorithm
{
    element_wise_addition,
    element_wise_multiplication,
    reduction_sum,
    reduction_product,
    fft,
    fft_convolution
};

enum class Hardware
{
    CPU,
    GPU
};

enum class MemoryAccess
{
    contiguous, // coalesced memory accesses on GPU
    interleaved // non-coalesced memory accesses on GPU
};

/*
 * parallelism = threads on CPU or instruction-level parallelism on GPU
 * block_size is only used for testing on a GPU
 */
auto test_performance(Algorithm alg,
                      int array_size,
                      int parallelism,
                      Hardware processor = Hardware::CPU,
                      MemoryAccess access = MemoryAccess::contiguous,
                      int block_size = default_block_size) -> ns;
} // namespace AT