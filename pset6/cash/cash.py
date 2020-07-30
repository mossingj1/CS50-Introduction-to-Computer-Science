from cs50 import get_float
from math import floor

# Program that first asks the user how much change is owed and then prints the minimum number
# of coins with which that change can be made.
# Assume only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).

def main():
    cents = get_change()
    num_coins = cents_to_coins(cents)
    print(num_coins)


def get_change():
    while True:
        change = get_float("Change owed: ")
        if change > 0:
            break
    cents = round(change * 100);
    return cents

def to_cents(change):
    cents = change
    return cents

def cents_to_coins(cents):
    quarters = floor(cents / 25);
    cents -= quarters*25

    dimes = floor(cents / 10)
    cents -= dimes*10

    nickels = floor(cents / 5)
    cents -= nickels * 5
    pennies = cents

    num_coins = quarters + dimes + nickels + pennies
    return num_coins

main()
