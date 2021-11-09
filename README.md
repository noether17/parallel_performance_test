# Overview
This repository is for testing the multithreaded performance of parallelizable algorithms on different hardware, and exploring the various factors that can affect performance.

# Testing Parameters
To get a good sense of how different variables can affect performance, a wide variety of tests must be conducted. These tests will employ algorithms of various complexities, a wide range of array sizes, multiple types of processors (both CPUs and GPUs), and different attempts at hardware optimization (and pessimization).

## Algorithms
Element-wise addition
Element-wise multiplication
Sum (by parallel reduction)
Product (by parallel reduction)
Fast Fourier Transform

## Array Sizes

## Hardware
### System 1
#### CPU
Intel i9 9900K
8 cores / 16 threads
5 GHz
3200 MHz Memory, Dual Channel

#### GPU
NVIDIA GTX 1070
1920 cores
~2 GHz
256 GB / s bandwidth

### System 2
#### CPU
Intel i7 10750H
6 cores / 12 threads
5 GHz
2400 MHz Memory, Dual Channel

#### GPU
NVIDIA GTX 1660 Ti Mobile
1536 cores
1590 MHz
288 GB / s bandwidth

## Optimizations
### CPU
Various numbers of software threads
Use of std::async
Bad use of cache (interleaving of data provided to threads)
Good use of cache (each thread gets a contiguous set of data)

### GPU
Various block sizes (multiples of 32)
Try block sizes smaller than 32 to observe negative impact on performance
Coalesced memory accesses
Non-coalesced memory accesses
Try to throw in example of warp divergence

# Variables to Measure
For the CPU tests, the measure of performance will be fairly straightforward -- just see how long a function takes to run. For the GPU tests, there is the additional factor of communicating data between the host system and the graphics card. It will therefore be interesting to measure both the execution time on the GPU, as well as the total time required to offboard the computation and return a result.