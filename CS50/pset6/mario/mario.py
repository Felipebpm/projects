from cs50 import get_int

# Asks height from user
while True:
    h = get_int("Height: ")
    if h in range(24):
        break
# Builds pyramid
for k in range(h):
    # add \n (h - k + 2) times
    print(" " * (h - k - 1), end='')
    print("#" * (k + 2), end='')
    print("")
