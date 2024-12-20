import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    # argv[2]: name of a CSV file containing the STR counts for a list of individuals
    # argv[3]: name of a text file containing the DNA sequence to identify.
    if len(argv) != 3:
        print("Missing command-line argument. Usage: python dna.py [file] [file]")
        sys.exit(1)

    database_fieldnames = []
    database_data = []
    # TODO: Read database file into a variable
    with open(argv[1], 'r') as file:
        reader = csv.DictReader(file)
        database_fieldnames = reader.fieldnames[1:]
        for row in reader:
            database_data.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(argv[2], 'r') as file:
        sequence = file.read()

    # TODO: Find longest match of each STR in DNA sequence
    result = {}
    for str_seq in database_fieldnames:
        result[str_seq] = str(longest_match(sequence, str_seq))

    # TODO: Check database for matching profiles
    for person in database_data:
        if result.items() <= person.items():
            print(person['name'])
            return
    else:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
