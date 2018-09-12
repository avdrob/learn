#!/usr/bin/python3


def lcs3(s1, s2, s3):
    L = [
            [
                [0 for k in range(len(s3) + 1)]
                for j in range(len(s2) + 1)
            ]
            for i in range(len(s1) + 1)
        ]

    for i in range(1, len(s1) + 1):
        for j in range(1, len(s2) + 1):
            for k in range(1, len(s3) + 1):
                if s1[i - 1] == s2[j - 1] == s3[k - 1]:
                    L[i][j][k] = 1 + L[i - 1][j - 1][k - 1]
                else:
                    L[i][j][k] = max(L[i - 1][j][k],
                                     L[i][j - 1][k],
                                     L[i][j][k - 1])

    return L[len(s1)][len(s2)][len(s3)]


if __name__ == '__main__':
    n = int(input())
    s1 = input().split()
    m = int(input())
    s2 = input().split()
    l = int(input())
    s3 = input().split()

    print(lcs3(s1, s2, s3))
