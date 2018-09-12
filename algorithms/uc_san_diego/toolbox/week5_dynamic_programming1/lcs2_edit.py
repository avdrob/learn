#!/usr/bin/python3


def edit_distance(s1, s2):
    'No substitutions allowed'
    E = [[]] * (len(s1) + 1)
    for i in range(len(s1) + 1):
        E[i] = [0] * (len(s2) + 1)

    for i in range(len(s1) + 1):
        E[i][0] = i
    for j in range(len(s2) + 1):
        E[0][j] = j

    for i in range(1, len(s1) + 1):
        for j in range(1, len(s2) + 1):
            distances = [E[i - 1][j] + 1, E[i][j - 1] + 1]
            if s1[i - 1] == s2[j - 1]:
                distances.append(E[i - 1][j - 1])
            E[i][j] = min(distances)

    return E[len(s1)][len(s2)]


def lcs2(s1, s2):
    return (len(s1) + len(s2) - edit_distance(s1, s2)) // 2


if __name__ == '__main__':
    n = int(input())
    s1 = input()
    m = int(input())
    s2 = input()

    s1 = s1.split()
    s2 = s2.split()
    print(lcs2(s1, s2))
