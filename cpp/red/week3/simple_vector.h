#include <stdexcept>
#include <sstream>
#include <algorithm>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() : data(nullptr), size(0), capacity(0) {}
    ~SimpleVector() { delete[] data; }

    SimpleVector(const SimpleVector &other)
        : data(new T[other.capacity]),
          size(other.size),
          capacity(other.capacity)
    {
        copy(other.begin(), other.end(), begin());
    }

    void operator=(const SimpleVector &other)
    {
        if (capacity < other.size) {
            delete[] data;
            data = new T[other.capacity];
            capacity = other.capacity;
        }
        size = other.size;
        copy(other.begin(), other.end(), begin());
    }

    explicit SimpleVector(size_t size)
        : data(new T[size]), size(size), capacity(size)
    {}

    T &operator[](size_t index)
    {
        if (index >= size) {
            stringstream ss;
            ss << "SimpleVector range check: "
               << "index (which is " << index << ") >= this->Size()"
               << " (which is " << size << ")";
            throw out_of_range(ss.str());
        }
        return data[index];
    }

    T *begin() { return data; }
    T *end() { return data + size; }
    const T *begin() const { return data; }
    const T *end() const {return data + size; }

    size_t Size() const { return size; };
    size_t Capacity() const { return capacity; }

    void PushBack(const T &value)
    {
        if (size == capacity) {
            reallocate();
        }
        data[size] = value;
        size++;
    }

private:
    static size_t next_pow2(size_t n)
    {
        size_t res = 1;
        while (res < n) {
            res <<= 1;
        }
        return res;
    }

    void reallocate()
    {
        if (capacity > 0) {
            capacity *= 2;
        }
        else {
            capacity = 1;
        }

        T *new_data = new T[capacity];
        copy(begin(), end(), new_data);
        delete[] data;
        data = new_data;
    }

    T *data;
    size_t size, capacity;
};
