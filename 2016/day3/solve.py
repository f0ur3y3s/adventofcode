with open("./input.txt") as file:
    lines = file.readlines();

total = 0

for line in lines:
    line = line.split()
    if (line[0] + line[1] > line[2]):
        print(f"{line[0]}\t{line[1]}\t{line[2]}")

        total += 1

print(total)