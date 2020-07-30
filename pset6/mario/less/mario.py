from cs50 import get_int
while True:
    h = get_int("Height: ")
    if h >= 0 and h <=8:
        break
space = h - 1
bricks = 1

for i in range (h):

    for i in range (space):
        print(" ", end = "")

    for i in range (bricks):
        print("#", end = "")

    print()

    space -= 1
    bricks += 1

