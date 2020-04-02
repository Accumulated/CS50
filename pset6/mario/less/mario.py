import cs50

# Validate user input
while True:
    i = cs50.get_int("Height: ")
    if i > 0 and i <= 8:
        break

# Buffer for height
w = i

# Outer loop for a new scanline
for x in range(0, i, 1):

    # Indentations before hashes
    for y in range(0, w-1, 1):
        print(" ", end="")

    # Rows of #
    for z in range(0, x+1, 1):
        print("#", end="")

    # Preparing a new scanline
    print()
    w -= 1
