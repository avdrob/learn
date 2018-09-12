#!/usr/bin/python3


from random import randint
from pprint import pprint


def lcs2(s1, s2):
    L = [[0 for j in range(len(s2) + 1)] for i in range(len(s1) + 1)]

    for i in range(1, len(s1) + 1):
        for j in range(1, len(s2) + 1):
            if s1[i - 1] == s2[j - 1]:
                L[i][j] = 1 + L[i - 1][j - 1]
            else:
                L[i][j] = max(L[i - 1][j], L[i][j - 1])

    return L[len(s1)][len(s2)]


if __name__ == '__main__':
    n = int(input())
    s1 = input()
    m = int(input())
    s2 = input()

    s1 = s1.split()
    s2 = s2.split()
    print(lcs2(s1, s2))
