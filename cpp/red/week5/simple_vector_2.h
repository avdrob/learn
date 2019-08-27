#include <cstdint>
#include <sstream>
#include <exception>

using namespace std;

template <typename T>
class SimpleVector {
public:
    SimpleVector() : data(nullptr), size(0), capacity(0) {}
    ~SimpleVector() { delete[] data; }
    SimpleVector(const SimpleVector& other) = delete;
    SimpleVector& operator=(const SimpleVector &other) = delete;

    SimpleVector(SimpleVector&& other)
        : data(other.data),
          size(other.size),
          capacity(other.capacity)
    {
        other.data = nullptr;
    }

    void operator=(SimpleVector &&other)
    {
        if (capacity < other.size) {
            delete[] data;
            data = new T[other.capacity];
            capacity = other.capacity;
        }
        size = other.size;
        move(other.begin(), other.end(), begin());
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

    void PushBack(const T& value)
    {
        if (size == capacity) {
            reallocate();
        }
        data[size] = value;
        size++;
    }

    void PushBack(T&& value)
    {
        if (size == capacity) {
            reallocate();
        }
        data[size] = move(value);
        size++;
    }

private:
    void reallocate()
    {
        if (capacity > 0) {
            capacity *= 2;
        }
        else {
            capacity = 1;
        }

        T *new_data = new T[capacity];
        move(begin(), end(), new_data);
        delete[] data;
        data = new_data;
    }

    T *data;
    size_t size, capacity;
};
