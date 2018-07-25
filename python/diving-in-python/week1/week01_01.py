import sys

digit_string = sys.argv[1]
sum = 0

for dig in digit_string:
    sum += int(dig)

print(sum)

"""
The true way:
    import sys

    print(sum([int(x) for x in sys.argv[1]]))
"""
