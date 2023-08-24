cmake_minimum_required(VERSION 3.22.1)
project(ParallelPerformanceTest CXX)
add_executable(parallel_perf_test parallel_perf_test.cpp)
set_property(TARGET parallel_perf_test PROPERTY CXX_STANDARD 17)

find_package(benchmark 1.8.2 REQUIRED) # Need version to differentiate Google benchmark from Anaconda3 benchmark
find_package(Threads REQUIRED)
target_link_libraries(parallel_perf_test benchmark::benchmark ${CMAKE_THREAD_LIBS_INIT})
target_compile_options(parallel_perf_test PRIVATE "-O3")