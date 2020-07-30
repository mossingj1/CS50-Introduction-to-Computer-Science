import cs50
from sys import argv

def main():
    # Check for correct number of command line arguments.
    if len(argv) != 2:
        print("Usage: roster.py House")
        exit(1)

    # Open SQL database
    db = cs50.SQL("sqlite:///students.db")

    # Query database for all students in the specified house
    # Students should be sorted alphabetically by last name then first name
    student_data = db.execute("SELECT * FROM students WHERE house = (?) ORDER BY last, first", argv[1])

    # Print out each students full name and birth year
    for i in range(len(student_data)):
        first = student_data[i]['first']
        middle = student_data[i]['middle']
        last = student_data[i]['last']
        birth = student_data[i]['birth']

        if middle != None:
            print(f"{first} {middle} {last}, born {birth}")
        else:
            print(f"{first} {last}, born {birth}")
main()

