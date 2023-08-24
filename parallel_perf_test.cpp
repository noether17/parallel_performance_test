#include <benchmark/benchmark.h>
#include <algorithm>
#include <execution>
#include <numeric>
#include <vector>

#define REPEAT2(X) X X
#define REPEAT4(X) REPEAT2(X) REPEAT2(X)
#define REPEAT8(X) REPEAT4(X) REPEAT4(X)
#define REPEAT16(X) REPEAT8(X) REPEAT8(X)
#define REPEAT32(X) REPEAT16(X) REPEAT16(X)
#define REPEAT(X) REPEAT32(X) REPEAT32(X)
auto constexpr macro_repetitions = 64;

using DataType = double;

class SingleThreadedElementWiseAddition
{
public:
    void setup(int items_per_operation)
    {
        left_operand_ = std::vector<DataType>(items_per_operation);
        std::iota(left_operand_.begin(), left_operand_.end(), static_cast<DataType>(0));
        right_operand_ = std::vector<DataType>(items_per_operation);
        std::iota(right_operand_.begin(), right_operand_.end(), static_cast<DataType>(0));
        result_ = std::vector<DataType>(items_per_operation);
    }

    auto execute()
    {
        return std::transform(std::execution::seq,
                              left_operand_.cbegin(),
                              left_operand_.cend(),
                              right_operand_.cbegin(),
                              result_.begin(),
                              std::plus<>{});
    }

private:
    std::vector<DataType> left_operand_{};
    std::vector<DataType> right_operand_{};
    std::vector<DataType> result_{};
};

void BM_single_threaded_element_wise_addition(benchmark::State& state)
{
    // test parameters
    auto const items_per_operation = state.range(0);
    auto const total_items = state.range(1); // need to keep total items constant so loop overhead doesn't dominate at small sizes
    auto const repetitions_of_operation = total_items / items_per_operation;
    auto const loops_per_iteration = repetitions_of_operation / macro_repetitions;

    // set up input data and reserve room for output
    auto tester = SingleThreadedElementWiseAddition{};
    tester.setup(items_per_operation);

    // test loop
    for (auto _ : state)
    {
        for (auto rep = 0; rep < loops_per_iteration; ++rep)
        {
            REPEAT(benchmark::DoNotOptimize(tester.execute());)
        }
    }
    state.SetItemsProcessed(total_items*state.iterations());
}

auto constexpr min_size = 1L<<5;
auto constexpr max_size = 1L<<28;
auto constexpr total_items_per_test = max_size * macro_repetitions;
BENCHMARK(BM_single_threaded_element_wise_addition)
    ->RangeMultiplier(2)
    ->Ranges({{min_size, max_size}, {total_items_per_test, total_items_per_test}})
    ->MeasureProcessCPUTime()
    ->UseRealTime();
BENCHMARK_MAIN();