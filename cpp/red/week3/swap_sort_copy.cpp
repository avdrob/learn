#include <vector>

using namespace std;

template <typename T>
void Swap(T *first, T *second)
{
    T temp = *first;
    *first = *second;
    *second = temp;
}

template <typename T>
void SortPointers(vector<T*> &pointers)
{
    for (size_t i = 0; i < pointers.size(); i++) {
        for (size_t j = pointers.size() - 1; j > i; j--) {
            if (*pointers[j] < *pointers[j - 1]) {
                Swap(&pointers[j], &pointers[j - 1]);
            }
        }
    }
}

template <typename T>
void SwapRange(T *range, size_t cnt)
{
    for (size_t i = 0; i < cnt / 2; i++) {
        Swap(&range[i], &range[cnt - 1 - i]);
    }
}

template <typename T>
void ReversedCopyDisjoint(T *src, size_t cnt, T *dest)
{
    for (size_t i = 0; i < cnt; i++) {
        dest[cnt - 1 - i] = src[i];
    }
}

template <typename T>
void ReversedCopy(T *src, size_t cnt, T *dest)
{
    if (dest >= src && dest < src + cnt) {
        SwapRange(dest, (src + cnt) - dest);
        ReversedCopyDisjoint(src, dest - src, src + cnt);
    }
    else if (src >= dest && src < dest + cnt) {
        SwapRange(src, (dest + cnt) - src);
        ReversedCopyDisjoint(dest + cnt, src - dest, dest);
    }
    else {
        ReversedCopyDisjoint(src, cnt, dest);
    }
}