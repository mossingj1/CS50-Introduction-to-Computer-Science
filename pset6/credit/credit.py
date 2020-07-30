from cs50 import get_int, get_string

amex_length = [15]
mstcrd_length = [16]
visa_length = [13, 16]
cc = get_string("Number: ")

# Luhn's Algorith to check card authenticity
every_other = []

for i in range(len(cc)-2,-1,-2):
    every_other.append(cc[i])

for x in every_other:
    every_other = every_other * 2


print(f"Every Other: {every_other}")