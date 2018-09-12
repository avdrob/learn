#!/usr/bin/python3


def fib_last_digit(n):
    a, b = 1, 0
    for _ in range(n):
        a, b = (a + b) % 10, a
    return b


if __name__ == '__main__':
    n = int(input())
    print(fib_last_digit(n))
