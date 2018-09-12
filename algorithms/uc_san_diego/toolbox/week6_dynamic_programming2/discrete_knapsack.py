#!/usr/bin/python3


def knapsack(W, w, v):
    value = [[0 for j in range(len(w) + 1)] for i in range(W + 1)]

    for cap in range(1, W + 1):
        for i in range(1, len(w) + 1):
            value[cap][i] = value[cap][i - 1]
            if cap >= w[i - 1]:
                value[cap][i] = max(value[cap][i],
                                    value[cap - w[i - 1]][i - 1] + v[i - 1])
    return value[W][len(w)]

if __name__ == '__main__':
    W, n = map(int, input().split())
    w = [int(it) for it in input().split()]
    print(knapsack(W, w, w))
