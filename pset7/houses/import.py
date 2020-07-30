import cs50
import csv
from sys import argv

def main():
    # Check for correct number of command line arguments.
    if len(argv) != 2:
        print("Usage: import.py characters.csv")
        exit(1)

    # Create database by opening and closing an empty file first
    open(f"students.db", "w").close()
    db = cs50.SQL("sqlite:///students.db")

    # Create table called `students`, and specify the columns names
    db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

    # Open CSV file
    with open(argv[1], "r") as input:

        # Create DictReader
        reader = csv.DictReader(input)

        #Iterate over each row in CSV file
        for row in reader:
            birth = int(row["birth"])

            # Parse full name to seperate columns (First | Middle | Last)
            name = row["name"]
            name_full = name.split(" ")
            first = name_full[0]
            x = len(name_full)
            if len(name_full) == 2:
                middle = None
                last = name_full[1]
            else:
                middle = name_full[1]
                last = name_full[2]

            # Insert show
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, row["house"], birth)

main()



