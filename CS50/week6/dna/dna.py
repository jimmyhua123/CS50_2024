import csv
import sys

def main():
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return

    # Read database file into a variable
    with open(sys.argv[1], 'r') as file:
        reader = csv.DictReader(file)
        database = list(reader)

    # Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as file:
        dna_sequence = file.read().strip()

    # Get STR sequences from the first line of the CSV file
    str_sequences = reader.fieldnames[1:]

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for str_sequence in str_sequences:
        str_counts[str_sequence] = longest_match(dna_sequence, str_sequence)

    # Check database for matching profiles
    for person in database:
        match = True
        for str_sequence in str_sequences:
            if int(person[str_sequence]) != str_counts[str_sequence]:
                match = False
                break
        if match:
            print(person['name'])
            return

    print("No match")

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        count = 0

        while True:
            start = i + count * subsequence_length
            end = start + subsequence_length

            if sequence[start:end] == subsequence:
                count += 1
            else:
                break

        longest_run = max(longest_run, count)

    return longest_run

if __name__ == "__main__":
    main()
