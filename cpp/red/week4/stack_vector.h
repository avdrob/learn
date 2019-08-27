#include <array>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
    explicit StackVector(size_t a_size = 0)
        : size_(a_size), data(array<T, N>())
    {
        if (a_size > N) {
            throw invalid_argument("");
        }
    }

    T &operator[](size_t index) { return data[index]; }
    const T &operator[](size_t index) const { return data[index]; }

    T *begin() { return &data[0]; }
    T *end() { return &data[size_ - 1] + 1; }
    const T *begin() const { return &data[0]; }
    const T *end() const { return &data[size_ - 1] + 1; }

    size_t Size() const { return size_; }
    size_t Capacity() const { return N; }

    void PushBack(const T &value)
    {
        if (size_ >= N) {
            throw overflow_error("");
        }
        data[size_++] = value;
    }

    T PopBack()
    {
        if (size_ == 0) {
            throw underflow_error("");
        }
        return data[--size_];
    }

private:
    size_t size_;
    array<T, N> data;
};