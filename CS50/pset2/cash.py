from cs50 import get_float

# Getting input
while True:
    c = get_float("Change owed: ")
    if (c > 0):
        break
# 25 cents
i = 0
if (c >= 0.2495):
    while True:
        c = c - 0.25
        i++
        if (c < 0.2495):
            break
# 10 cents
if (c >= 0.0995):
    while True:
        c = c - 0.10
        i++
        if (c < 0.0995):
            break
# 5 cents
if (c >= 0.0495):
    while True:
        c = c - 0.05
        i++
        if (c < 0.0495):
            break
# 1 cent
if (c >= 0.009):
    while True:
        c = c - 0.01
        i++
        if (c < 0.009):
            break
# Displaying result
    print(f"{i}", i)