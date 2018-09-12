#!/usr/bin/python3


import re
from math import inf
from pprint import pprint


def min_and_max(i, j):
    min_val, max_val = inf, -inf

    for k in range(i, j):
        a = eval(str(M[i][k]) + op[k - 1] + str(M[k + 1][j]))
        b = eval(str(M[i][k]) + op[k - 1] + str(m[k + 1][j]))
        c = eval(str(m[i][k]) + op[k - 1] + str(M[k + 1][j]))
        d = eval(str(m[i][k]) + op[k - 1] + str(m[k + 1][j]))
        min_val = min(min_val, a, b, c, d)
        max_val = max(max_val, a, b, c, d)

    return min_val, max_val


def parens():
    for i in range(1, len(d) + 1):
        m[i][i], M[i][i] = d[i - 1], d[i - 1]

    for s in range(1, len(d)):
        for i in range(1, len(d) - s + 1):
            j = i + s
            m[i][j], M[i][j] = min_and_max(i, j)

    return M[1][len(d)]

if __name__ == '__main__':
    s = input()
    d = [int(x) for x in re.split('[-+*]', s)]
    op = re.findall('[-+*]', s)

    M = [[0 for j in range(len(d) + 1)] for i in range(len(d) + 1)]
    m = [[0 for j in range(len(d) + 1)] for i in range(len(d) + 1)]

    print(parens())
