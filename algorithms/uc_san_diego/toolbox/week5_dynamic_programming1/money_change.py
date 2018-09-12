#!/usr/bin/python3


coins = (1, 3, 4)


def change_money(money):
    min_coins = [0] * (money + 1)

    for i in range(1, money + 1):
        ways = []
        for c in coins:
            if i >= c:
                ways.append(min_coins[i-c])
            min_coins[i] = min(ways) + 1
    return min_coins[money]


if __name__ == '__main__':
    money = int(input())
    print(change_money(money))
