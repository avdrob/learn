#!/usr/bin/python3

import random

def merge(a, low, mid, high):
    lhalf = a[low:mid + 1]
    rhalf = a[mid + 1:high + 1]

    i, j = 0, 0
    rput = 0
    res = 0
    while i < len(lhalf) and j < len(rhalf):
        if lhalf[i] <= rhalf[j]:
            a[low + i + j] = lhalf[i]
            i += 1
            res += rput
        else:
            a[low + i + j] = rhalf[j]
            j += 1
            rput += 1
    if i >= len(lhalf):
        while j < len(rhalf):
            a[low + i + j] = rhalf[j]
            j += 1
            rput += 1
    elif j >= len(rhalf):
        while i < len(lhalf):
            a[low + i + j] = lhalf[i]
            i += 1
            res += rput
    return res

def merge_sort(a, low, high):
    if low == high:
        return 0

    mid = low + (high - low) // 2
    res = merge_sort(a, low, mid)
    res += merge_sort(a, mid + 1, high)
    res += merge(a, low, mid, high)

    return res


# def stress_test():
#     while True:
#         a = [0] * 10
#         for i in range(10):
#             a[i] = random.randint(0, 100)
#         b = a.copy()
# 
#         print('#' * 40)
#         print('Test case:', a)
#         merge_sort(a, 0, len(a) - 1)
#         b = sorted(b)
#         if (a == b):
#             print('OK')
#             print('#' * 40)
#             print('')
#         else:
#             print('WRONG ANSWER')
#             print('Expected result:', b)
#             print('Obtained result:', a)
#             break


if __name__ == '__main__':
    n = int(input())
    a = list(map(int, input().split()))
    print(merge_sort(a, 0, len(a) - 1))
