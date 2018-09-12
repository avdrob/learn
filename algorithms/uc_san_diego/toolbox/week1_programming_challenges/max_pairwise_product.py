# python3


max_ints = [0, 0]


def fits(a):
    return a > max_ints[0]


def insert(a):
    max_ints[0] = a
    if max_ints[0] > max_ints[1]:
        max_ints[0], max_ints[1] = max_ints[1], max_ints[0]


def max_pairwise_product(numbers):
    for n in numbers:
        if fits(n):
            insert(n)

    return max_ints[0] * max_ints[1]


if __name__ == '__main__':
    input_n = int(input())
    input_numbers = [int(x) for x in input().split()]
    print(max_pairwise_product(input_numbers))
