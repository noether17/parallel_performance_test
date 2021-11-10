#include "AlgorithmTester.hpp"

namespace AT
{
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

    // Determine algorithm

    // create input vector(s)

    // create vector of threads

    // start timer
    // start threads
    // join threads
    // end timer

    // return execution time
}
} // namespace AT