#include <queue>
#include <set>
#include <stdexcept>

using namespace std;

template <class T>
class ObjectPool {
public:
    T *Allocate()
    {
        T *res;
        if (!freed.empty()) {
            res = freed.front();
            freed.pop();
        }
        else {
            res = new T;
        }
        allocated.insert(res);
        return res;
    }

    T * TryAllocate()
    {
        T *res = nullptr;
        if (!freed.empty()) {
            res = freed.front();
            freed.pop();
            allocated.insert(res);
        }
        return res;
    }

    void Deallocate(T *object)
    {
        auto it = allocated.find(object);
        if (it != allocated.end()) {
            allocated.erase(it);
            freed.push(object);
        }
        else {
            throw invalid_argument("Invalid object for deallocation");
        }
    }

    ~ObjectPool()
    {
        for (T *obj : allocated) {
            delete obj;
        }
        allocated.clear();
        while (!freed.empty()) {
            T *obj = freed.front();
            freed.pop();
            delete obj;
        }
    }

private:
    set<T*> allocated;
    queue<T*> freed;
};