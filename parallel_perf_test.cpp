#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

constexpr auto number_of_array_sizes = 20;

using data_type = int;

int main()
{
    // create vector of array sizes
    auto array_sizes = std::vector<int>(number_of_array_sizes);
    std::iota(array_sizes.begin(), array_sizes.end(), 0); // fill with powers
    std::transform(array_sizes.begin(), array_sizes.end(), array_sizes.begin(),
                   [](auto x){ return pow(2, x); }); // set to powers of 2
    
    // create vector of input values
    auto input_values = std::vector<data_type>(array_sizes.back());
    std::iota(input_values.begin(), input_values.end(), 1);

    // create vector for storing execution times
    using ns = std::chrono::nanoseconds;
    auto execution_times = std::vector<ns>();

    for (auto current_array_size : array_sizes)
    {
        // create array to store output
        auto output_values = std::vector<data_type>();

        // start timer
        auto start = std::chrono::high_resolution_clock::now();

        // execute function
        for (auto i = 0; i < current_array_size; ++i)
        {
            auto value = input_values.at(i);
            output_values.emplace_back(value * value);
        }

        // stop timer
        auto end = std::chrono::high_resolution_clock::now();

        // push execution time
        execution_times.emplace_back(end - start);

        // print output
        for (auto y : output_values)
        {
            //std::cout << y << '\n';
        }
        std::cout << "execution time: "
                  << execution_times.back().count()
                  << " ns\n";
    }

    return 0;
}