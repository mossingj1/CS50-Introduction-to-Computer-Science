from cs50 import get_string

def main():
    text = get_string("Text: ")
    text = text.lower()

    letters = count_letters(text)
    words = text.count(" ") + 1
    sent = text.count(".") + text.count("!") + text.count("?")

    l = letters * 100/words
    s = sent * 100/words
    index = 0.0588 * l - 0.296 * s - 15.8

    print_ans(index)

    print(f"Letters: {letters}")
    print(f"Words: {words}")
    print(f"Sentances: {sent}")

def count_letters(text):
    count = 0
    for i in range(len(text)):
        if ord(text[i]) >= 97 and ord(text[i]) <= 122:
            count += 1
    return count

def print_ans(index):
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

main()