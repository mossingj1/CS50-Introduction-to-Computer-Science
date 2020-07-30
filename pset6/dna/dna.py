from sys import argv
import csv

def main():
    # Check for correct number of command line arguments.
    if len(argv) != 3:
        print("Usage: TBD")
        exit(1)

    # Extract names and individual SRT values from CSV file
    data = get_data(argv[1])

    # List of SRT's in CSV file
    SRT = data[0]

    # List of names in CSV file
    names = data[1]

    # List of SRT values in CSV file
    # Value index position matches SRT name index position
    people_dna = data[2]

    # Computes longest consecutive repeats of the STRs in a list format.
    SRT_count = seq_counter(SRT, argv[2])

    # Returns the name of match
    matched_name = match_srt(SRT_count, people_dna, names)

    print(matched_name)

# Reads CSV file and outputs list of People, SRT Names, and SRT count values
def get_data(file):
    with open(file) as csvfile:
        # Get SRT Names by reading first row
        first_line = csvfile.readline().strip()
        SRT = first_line.split(',')
        SRT.pop(0)

        # Get names of people by reading the first sting in each row
        people = []
        people_dna = []
        reader = csv.reader(csvfile)

        # Get SRT count values
        for row in reader:
            person = row[0]
            people.append(person)
            person_dna = row[1:]
            # Converts value from a string to an intiger
            for i in range(0, len(person_dna)):
                person_dna[i] = int(person_dna[i])
            people_dna.append(person_dna)

    return SRT, people, people_dna

# Evaluates if the string (str) is a sequence of repeated patterns (self)
# https://leetcode.com/problems/repeated-substring-pattern/discuss/94334/
def repeatedSubstringPattern(self, str):
    return str in (2 * str)[1:-1]

# Matches the list of SRT counts to a name
def match_srt(SRT_count, people_dna, names):
    person = "No match"
    for i in range(0,len(people_dna)):
        if SRT_count == people_dna[i]:
            person = names[i]
            break
    return person

def seq_counter(SRT, file):

    # Open DNA file for reading
    dna_seq = open(file, "r")
    dna_seq = dna_seq.read()

    # Initilize SRT counter
    SRT_count = [0] * len(SRT)

    # Initilize Variables
    i = 0
    l = 0
    n = 0

    # Max length of SRT
    max_length = len(max(SRT, key=len))

    while l <= len(dna_seq):
        for j in range(i+1,i+max_length+1):
            n = 0
            tmp_str = dna_seq[i:j]
            if tmp_str in SRT:
                pattern = tmp_str
                index = SRT.index(pattern)
                n = 1
                # Records maximum sequence count (if 1)
                if n > SRT_count[index]:
                    SRT_count[index] = n
                while repeatedSubstringPattern(pattern, dna_seq[i:j+len(pattern)]) == True and j <= len(dna_seq):
                    n += 1
                    j += len(pattern)
                    # Records maximum sequence count
                    if n > SRT_count[index]:
                        SRT_count[index] = n
        i = i + 1
        l = i + 1
        n = 0
    return SRT_count
main()



