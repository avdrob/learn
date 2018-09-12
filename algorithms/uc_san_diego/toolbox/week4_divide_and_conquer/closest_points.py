#!/usr/bin/python3

import math
import random


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __str__(self):
        return "Point({}, {})".format(self.x, self.y)

    def __repr__(self):
        return "({}, {})".format(self.x, self.y)
    

def dist(p1, p2):
    return math.sqrt((p1.x - p2.x) ** 2 + (p1.y - p2.y) ** 2)


def min_dist(points, low, high):
    if high - low + 1 == 1:
        return -1
    elif high - low + 1 == 2:
        return dist(points[low], points[high])

    mid = low + (high - low) // 2
    mid_line = points[mid].x + (points[mid + 1].x - points[mid].x) / 2.0

    d1 = min_dist(points, low, mid)
    d2 = min_dist(points, mid + 1, high)
    if d1 == -1:
        d1 = d2
    elif d2 == -1:
        d2 = d1

    d = min(d1, d2)
    strip = []
    for i in range(low, high + 1):
        if abs(points[i].x - mid_line) <= d:
            strip.append(points[i])
    
    strip.sort(key=lambda p: p.y)
    d_pr = d
    for i in range(len(strip)):
        for j in range(i + 1, len(strip)):
            if j - i > 7:
                break
            if abs(strip[i].y - strip[j].y) < d_pr:
                d_pr = min(d_pr, dist(strip[i], strip[j]))

    return min(d, d_pr)


def min_dist_dumb(points):
    d = dist(points[0], points[1])
    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            d = min(d, dist(points[i], points[j]))
    return d


def stress_test():
    n = 5
    points = [None] * n

    while True:
        for i in range(n):
            points[i] = Point(random.randint(-4, 4),
                              random.randint(-4, 4))
        
        points.sort(key=lambda p: p.x)
        print('#' * 60)
        print('Test case:', points)
        d = min_dist(points, 0, len(points) - 1)
        dd = min_dist_dumb(points)
        if d == dd:
            print('OK')
            print('#' * 60)
            print('\n')
        else:
            print('WRONG ANSWER')
            print('Expected result:', dd)
            print('Obtained result:', d)
            print('#' * 60)
            print('\n')
            break


if __name__ == '__main__':
    n = int(input())
    points = [None] * n
    for i in range(n):
        x, y = map(int, input().split())
        points[i] = Point(x, y)
    
    points.sort(key=lambda p: p.x)
    print("{:.4f}".format(min_dist(points, 0, len(points) - 1)))
    # stress_test()