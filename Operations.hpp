#include "MappingPolicy.hpp"
#include <thread>
#include <vector>

namespace PPT
{
    template <typename T>
    using v_iter = std::vector<T>::iterator;
    template <typename T>
    using v_citer = std::vector<T>::const_iterator;

    /*
    // Abstract Operations
    // these provide interfaces establishing the input/output
    // requirements of each operation

    // A Combination takes two input vectors and produces one output vector
    template <typename T>
    class Combination
    {
        public:
        class WorkSegment
        {
            std::thread tid;
            v_citer<T> a_begin;
            v_citer<T> a_end;
            v_citer<T> b_begin;
            v_citer<T> b_end;
            v_iter<T>  out_begin;
            v_iter<T>  out_end;
            int        stride;
        };
        virtual ~Combination() = 0;
        virtual auto operator()(T a, T b) -> T = 0;
        virtual auto operator()(std::vector<WorkSegment>) -> void = 0;
    };

    // A Transformation takes one input vector and returns one output vector
    template <typename T>
    class Transformation
    {
        public:
        class WorkSegment
        {
            std::thread tid;
            v_citer<T> in_begin;
            v_citer<T> in_end;
            v_iter<T>  out_begin;
            v_iter<T>  out_end;
            int        stride;
        };
        virtual ~Transformation() = 0;
        virtual auto operator()(std::vector<WorkSegment>&) -> void = 0;
    };

    // A Reduction takes one input vector and returns a scalar
    template <typename T>
    class Reduction
    {
        public:
        class WorkSegment
        {
            std::thread tid;
            v_citer<T> in_begin;
            v_citer<T> in_end;
            T          result;
            int        stride;
        };
        virtual ~Reduction() = 0;
        virtual auto operator()(std::vector<WorkSegment>&) -> void = 0;
    };
    */

    // Concrete Operations
    template <typename T>
    class ElementWiseAddition
    {
    public:
        ElementWiseAddition(int size, int n_threads)
            : data_{size},
              threads_(n_threads)
        {}

        auto operator() -> void;

    private:
        CombinationMapping<T> data_{};
        std::vector<std::thread> threads_{};
    };
} // namespace PPT