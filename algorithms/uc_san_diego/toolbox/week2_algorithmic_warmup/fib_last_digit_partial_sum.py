#!/usr/bin/python3


def pisano_num(m):
    if m < 2:
        return 1
    a, b = 1, 0
    i, j = -1, -1
    res = 0
    while True:
        a, b = a + b, a
        i, j = j, a % m
        res += 1
        if (i, j) == (0, 1):
            break
    return res


def fib(n):
    a, b = 1, 0
    for _ in range(n):
        a, b = a + b, a
    return b


def sum_last_digit(n):
    return (fib(n % pisano_num(10)) - 1) % 10


if __name__ == '__main__':
    m, n = map(int, input().split())
    print((10 + sum_last_digit(n + 2) - sum_last_digit(m + 1)) % 10)
