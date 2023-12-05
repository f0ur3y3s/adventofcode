

# with open("test.txt", "r") as file:
#     data = file.read().splitlines()

# print(data)
# seeds = []
# seeds = data[0].split(": ")[1].split(" ")
# print(seeds)

# dont forget to add a new line in the input file
with open("test.txt", "r") as file:
    data = file.read()

# Split the data into sections based on the empty lines
sections = [section.strip() for section in data.strip().split('\n\n')]

# Create a dictionary to store the title: data relationship
result_dict = {}

# Iterate through sections and extract title: data pairs
for section in sections:
    lines = section.split('\n')
    title = lines[0].strip(':')
    data_lines = [line.split() for line in lines[1:]]
    data = [[int(value) for value in row] for row in data_lines]
    result_dict[title] = data

# Print the result dictionary
for title, data in result_dict.items():
    print(f"{title} ---")
    for row in data:
        print(row)
    print()

seeds = result_dict["seeds"][0]
print(seeds)

def apply_mapping(category_map, number):
    for dest_start, source_start, length in category_map:
        if source_start <= number < source_start + length:
            return dest_start + (number - source_start)
    return number

def find_lowest_location(seeds, maps):
    current_numbers = seeds.copy()
    
    for category_map in maps:
        next_numbers = []
        for number in current_numbers:
            mapped_number = apply_mapping(category_map, number)
            next_numbers.append(mapped_number)
        current_numbers = next_numbers
    
    return min(current_numbers)

result = find_lowest_location(seeds, result_dict["seed-to-soil map"])
print(result)