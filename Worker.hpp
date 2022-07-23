#include <thread>

template <typename IteratorType>
class StrideIterator
{
public:
    StrideIterator(IteratorType iter, int stride = 1)
      : iter_ {iter},
        stride_ {stride}
    {}
    auto operator++() -> StrideIterator&
    {
        this->iter_ += stride_;
        return *this;
    }
private:
    IteratorType iter_;
    int stride_;
};

template <typename Callable, typename RangeType>
class Worker
{
    // The Worker should have an iterator and a sentinel specialized
    // to iterate through the given operation
public:
    Worker(Callable f, RangeType range)
    {
        thread_ = std::thread{[&](){ for (auto& element : range) { f(element); }}};
    }
private:
    std::thread thread_;
    RangeType range_;
    //StrideIterator<IteratorType> begin_;
    //StrideIterator<IteratorType> end_;
};