#!/usr/bin/python3

import bisect


if __name__ == '__main__':
    s, p = map(int, input().split())
    a, b = [0] * s, [0] * s
    for i in range(s):
        a[i], b[i] = map(int, input().split())
    x = map(int, input().split())

    a.sort()
    b.sort()
    res = 0
    for p in x:
        begins = bisect.bisect_right(a, p)
        ends = bisect.bisect_left(b, p)
        print(begins - ends, end=' ')
    print('\n')
