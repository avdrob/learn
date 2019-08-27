#include <vector>
#include <stdexcept>
#include <sstream>

using namespace std;

template <typename T>
class Deque {
public:
    Deque() {}
    bool Empty() const { return Size() == 0; }
    void PushFront(T val) { deque_front.push_back(val); }
    void PushBack(T val) { deque_back.push_back(val); }

    T &operator[](size_t index)
    {
        if (index < deque_front.size()) {
            return deque_front[deque_front.size() - 1 - index];
        }
        else {
            return deque_back[index - deque_front.size()];
        }
    }

    const T &operator[](size_t index) const
    {
        if (index < deque_front.size()) {
            return deque_front[deque_front.size() - 1 - index];
        }
        else {
            return deque_back[index - deque_front.size()];
        }
    }

    T &At(size_t index)
    {
        if (index >= Size()) {
            ostringstream iss;
            iss << "Index " << index << "is out of range";
            throw out_of_range(iss.str());
        }
        else {
            return operator[](index);
        }
    }

    const T &At(size_t index) const
    {
        if (index >= Size()) {
            ostringstream iss;
            iss << "Index " << index << "is out of range";
            throw out_of_range(iss.str());
        }
        else {
            return operator[](index);
        }
    }

    size_t Size() const
    {
        return deque_front.size() + deque_back.size();
    }

    T &Front()
    {
        if (!deque_front.empty()) {
            return deque_front.back();
        }
        else {
            return deque_back.front();
        }
    }

    const T &Front() const
    {
        if (!deque_front.empty()) {
            return deque_front.back();
        }
        else {
            return deque_back.front();
        }
    }

    T &Back()
    {
        if (!deque_back.empty()) {
            return deque_back.back();
        }
        else {
            return deque_front.front();
        }
    }

    const T &Back() const
    {
        if (!deque_back.empty()) {
            return deque_back.back();
        }
        else {
            return deque_front.front();
        }
    }


private:
    vector<T> deque_front;
    vector<T> deque_back;
};