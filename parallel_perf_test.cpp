#include <benchmark/benchmark.h>
#include <algorithm>
#include <execution>
#include <numeric>
#include <vector>

using DataType = double;

void BM_single_threaded_element_wise_addition(benchmark::State& state)
{
    // test parameters
    auto const items_per_operation = state.range(0);
    auto const total_items = state.range(1); // need to keep total items constant so loop overhead doesn't dominate at small sizes
    auto const repetitions_of_operation = total_items / items_per_operation;

    // set up input data and reserve room for output
    auto left_operand = std::vector<DataType>(items_per_operation);
    std::iota(left_operand.begin(), left_operand.end(), static_cast<DataType>(0));
    auto right_operand = std::vector<DataType>(items_per_operation);
    std::iota(right_operand.begin(), right_operand.end(), static_cast<DataType>(0));
    auto result = std::vector<DataType>(items_per_operation);

    // test loop
    for (auto _ : state)
    {
        for (auto rep = 0; rep < repetitions_of_operation; ++rep)
        {
            benchmark::DoNotOptimize(
                std::transform(std::execution::seq,
                               left_operand.cbegin(),
                               left_operand.cend(),
                               right_operand.cbegin(),
                               result.begin(),
                               std::plus<>{})
            );
        }
    }
    state.SetItemsProcessed(total_items*state.iterations());
}

BENCHMARK(BM_single_threaded_element_wise_addition)->RangeMultiplier(2)->Ranges({{1<<5, 1<<28}, {1<<28, 1<<28}})->MeasureProcessCPUTime()->UseRealTime();
BENCHMARK_MAIN();