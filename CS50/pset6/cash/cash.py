from cs50 import get_float

# Getting input
while True:
    c = get_float("Change owed: ")
    if (c >= 0):
        break
c = c * 100
i = 0
# 25 cents
i = c // 25
c = c % 25
# 10 cents
i += c // 10
c = c % 10
# 5 cents
i = i + c // 5
c = c % 5
# 1 cent
i += c // 1
c = c % 1
# Displaying result
print(f"{i}")