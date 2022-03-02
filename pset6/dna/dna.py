import sys
import csv

# ensure correct usage
if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py DATABASE SEQUENCE")

# pset says assume database and sequence input correctly

# read files, create list of dictionaries of humans in database, plus list of STRs to look for
db = open(sys.argv[1], "r")
dbreader = csv.DictReader(db)
STRs = dbreader.fieldnames
seq = open(sys.argv[2], "r").read().rstrip()

# prep dict for results of search and list of possible lengths
lengths = set()
sample = {}
for STR in STRs[1:]:
    sample[STR] = 0
    lengths.add(len(STR))

# gives length of sequence of an STR given starting position
def repeats(start, STR, length, count):
    if seq[start:start + length] == STR:
        return repeats(start + length, STR, length, count + 1)
    else:
        return count

# search for nucleotides in the sequence, return dict of STRs
i = 0
while i < len(seq):
    for STRlen in lengths:
        check = seq[i:i + STRlen]
        if check in STRs:
            num = repeats(i, check, STRlen, 0)
            if sample[check] < num:
                sample[check] = num
                #print(f"{seq[i:i + num * STRlen]} at {i}")
                #print(f"seq of {check} of length {num} at {i}")
                #print(f"following {seq[i-STRlen:i]}")
            i += (STRlen * num) - (STRlen - 1)
            break
    i += 1

# see if there is a match
for row in dbreader:
    matches = 0
    for STR in STRs[1:]:
        if int(row[STR]) == sample[STR]:
            matches += 1
        if matches == len(STRs) - 1:
            sys.exit(f"{row['name']}")
sys.exit("No match")