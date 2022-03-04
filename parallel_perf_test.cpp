#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

constexpr auto number_of_array_sizes = 20;

using data_type = int;
using ns = std::chrono::nanoseconds;

auto get_array_sizes(int n_sizes) -> std::vector<int>;

template <typename DataType>
auto generate_input(int max_size) -> std::vector<DataType>;

template <typename CallableType>
auto measure_execution_time(CallableType f, int array_size) -> ns;

template <typename CallableType>
auto generate_performance_profile(CallableType f, int number_of_array_sizes) -> std::vector<ns>;

int main()
{
    generate_performance_profile([](auto value){return value*value;}, number_of_array_sizes);
    return 0;
}

auto get_array_sizes(int n_sizes) -> std::vector<int>
{
    auto array_sizes = std::vector<int>(number_of_array_sizes);
    std::iota(array_sizes.begin(), array_sizes.end(), 0); // fill with powers
    std::transform(array_sizes.begin(), array_sizes.end(), array_sizes.begin(),
                   [](auto x){ return pow(2, x); }); // set to powers of 2
    return array_sizes;
}

template <typename DataType>
auto generate_input(int max_size) -> std::vector<DataType>
{
    auto input_values = std::vector<DataType>(max_size);
    std::iota(input_values.begin(), input_values.end(), 1);
    return input_values;
}

template <typename CallableType>
auto measure_execution_time(CallableType f, int array_size) -> ns
{
    auto input_values = generate_input<data_type>(array_size);
    auto output_values = std::vector<data_type>(array_size);

    // start timer
    auto start = std::chrono::high_resolution_clock::now();

    // execute function
    for (auto i = 0; i < array_size; ++i)
    {
        auto value = input_values.at(i);
        output_values.emplace_back(f(value));
    }

    // stop timer
    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}

template <typename CallableType>
auto generate_performance_profile(CallableType f, int number_of_array_sizes) -> std::vector<ns>
{
    auto array_sizes = get_array_sizes(number_of_array_sizes);
    auto execution_times = std::vector<ns>();

    for (auto current_array_size : array_sizes)
    {
        // push execution time
        execution_times.emplace_back(measure_execution_time(f, current_array_size));

        //// print output
        //for (auto y : output_values)
        //{
        //    //std::cout << y << '\n';
        //}
        std::cout << "execution time: "
                  << execution_times.back().count()
                  << " ns\n";
    }

    return execution_times;
}