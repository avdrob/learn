#!/usr/bin/python3


def edit_distance(s1, s2):
    E = [[]] * (len(s1) + 1)
    for i in range(len(s1) + 1):
        E[i] = [0] * (len(s2) + 1)

    for i in range(len(s1) + 1):
        E[i][0] = i
    for j in range(len(s2) + 1):
        E[0][j] = j

    for i in range(1, len(s1) + 1):
        for j in range(1, len(s2) + 1):
            E[i][j] = min(
                E[i - 1][j] + 1,
                E[i][j - 1] + 1,
                E[i - 1][j - 1] + int(not s1[i - 1] == s2[j - 1])
            )

    return E[len(s1)][len(s2)]


if __name__ == '__main__':
    s1 = input()
    s2 = input()
    print(edit_distance(s1, s2))
