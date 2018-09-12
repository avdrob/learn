#!/usr/bin/python3

from pprint import pprint


def backtrack(value, W, w, v):
    cap = W
    res = []
    for i in range(len(w), 0, -1):
        if value[cap][i] > value[cap][i - 1]:
            res.append(v[i - 1])
            cap -= w[i - 1]
    return res


def knapsack(W, w, v):
    value = [[0 for j in range(len(w) + 1)] for i in range(W + 1)]

    for cap in range(1, W + 1):
        for i in range(1, len(w) + 1):
            value[cap][i] = value[cap][i - 1]
            if cap >= w[i - 1]:
                value[cap][i] = max(value[cap][i],
                                    value[cap - w[i - 1]][i - 1] + v[i - 1])
    return value[W][len(w)], backtrack(value, W, w, v)


if __name__ == '__main__':
    n = int(input())
    w = [int(x) for x in input().split()]

    s = sum(w)
    if s % 3 != 0:
        print(0)
        exit()

    w.sort(reverse=True)

    val1, set1 = knapsack(s // 3, w, w)
    if val1 != s // 3:
        print(0)
        exit()

    for el in sorted(set1, reverse=True):
        w.remove(el)
    val2, set2 = knapsack(s // 3, w, w)
    if val2 != s // 3:
        print(0)
        exit()

    print(1)
