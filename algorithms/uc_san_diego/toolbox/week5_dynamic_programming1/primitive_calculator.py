#!/usr/bin/python3


def calculate(n):
    min_ops = [0] * (n + 1)
    min_ops[1] = [1]

    for i in range(2, n + 1):
        seqs = [min_ops[i - 1]]
        if i % 2 == 0:
            seqs.append(min_ops[i // 2])
        if i % 3 == 0:
            seqs.append(min_ops[i // 3])

        min_ops[i] = min(seqs, key=lambda seq: len(seq)).copy()
        min_ops[i].append(i)

    return min_ops[n]


if __name__ == '__main__':
    n = int(input())
    seq = calculate(n)
    print(len(seq) - 1)
    print(seq)
