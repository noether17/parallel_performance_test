#include "Operations.hpp"

namespace PPT
{
    template <typename Operation>
    class ParallelPerformanceTester
    {
        // free parameters:
        //      operation
        //      array size
        //      number of trials
        //      number of threads
        //      memory access policy (interleaved or contiguous)
        //      data type
        //      instruction-level parallelism
        //      processor
        //      block size (GPU only)
        //      warp divergence (GPU only)
    public:
        ParallelPerformanceTester(int size, int n_threads, int n_trials)
            : op_{size, n_threads},
              n_trials_{n_trials}
        {}

    private:
        Operation op_{};
        int n_trials_{};
    };
} // namespace PPT