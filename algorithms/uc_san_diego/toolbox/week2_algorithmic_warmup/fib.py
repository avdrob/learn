#!/usr/bin/python3


def fib(n):
    a, b = 1, 0
    for _ in range(n):
        a, b = a + b, a
    return b


n = int(input())
print(fib(n))
