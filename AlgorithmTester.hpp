#pragma once

#include <vector>

namespace AT
{
enum class Algorithm
{
    element_wise_addition,
    element_wise_multiplication,
    reduction_sum,
    reduction_product,
    fft
};

enum class CacheStrategy
{
    contiguous,
    interleaved
};

class AlgorithmTester
{
    public:
    // delete special member functions
    AlgorithmTester() = delete;
    AlgorithmTester(const AlgorithmTester&) = delete;
    AlgorithmTester(AlgorithmTester&&) = delete;
    auto operator=(const AlgorithmTester&) -> AlgorithmTester& = delete;
    auto operator=(AlgorithmTester&&) -> AlgorithmTester& = delete;

    // custom constructor
    AlgorithmTester(Algorithm alg, int threads, CacheStrategy cs)
        : alg_{alg}, threads_{threads}, cs_{cs} {}
    
    // function call
    template <typename T>
    auto operator()(std::vector<T>& result, const std::vector<T>& a,
                    const std::vector<T>& b) -> void;

    private:
    Algorithm     alg_;
    int           threads_{1};
    CacheStrategy cs_;
};

template <typename T>
auto AlgorithmTester::operator()(std::vector<T>& result,
                                 const std::vector<T>& a,
                                 const std::vector<T>& b) -> void
{
    // TODO
    // check member variables
    // pass work off to threads, as appropriate
}
} // namespace AT