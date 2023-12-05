def parse_data(filename):
    # dont forget to add a new line in the input file
    with open(filename, "r") as file:
        raw_data = file.read()

    sections = [section.strip() for section in raw_data.strip().split("\n\n")]
    data = {}

    for section in sections:
        lines = section.split("\n")
        title = lines[0].strip(":")
        raw_data_lines = [line.split() for line in lines[1:]]
        raw_data = [[int(value) for value in row] for row in raw_data_lines]
        data[title] = raw_data

    return data


def apply_mapping(mapping, seeds):
    # mapping = dst range start, src range start, range length
    dst_start = mapping[0]
    src_start = mapping[1]
    range_len = mapping[2]
    src_end = src_start + range_len - 1
    dst_end = dst_start + range_len - 1
    print("-" * 50)
    print(f"SRC Range: {src_start} - {src_end}")
    print(f"DST Range: {dst_start} - {dst_end}")
    print(f"Seeds: {seeds}")

    new_seeds = seeds
    for seed, mod in seeds.items():
        if mod == 0:
            if seed in range(src_start, src_end + 1):
                translated_seed = dst_start + (seed - src_start)
                # new_seeds[seed] = 1
                # new_seeds[translated_seed] = new_seeds.pop(seed)
    print(f"New seeds: {new_seeds}")

    # for idx, seed in enumerate(seeds):
    #     if seed in range(src_start, src_end + 1):
    #         translated_seed = dst_start + (seed - src_start)
    #         # print(f"translation\t{seed}\t{translated_seed}")
    #         seeds[idx] = translated_seed
    #         print(seeds)

    print("-" * 50)
    return new_seeds


data = parse_data("test.txt")
seeds = data["seeds"][0]
data.pop("seeds", None)

# new_seeds = {}
# for seed in seeds:
#     new_seeds[seed] = 0
# print(new_seeds)
def gen_new_seeds(seeds):
    new_seeds = {}
    for seed in seeds:
        new_seeds[seed] = 0
    return new_seeds

print(data)
for title, mapping_arr in data.items():
    new_seeds = gen_new_seeds(seeds)
    print(new_seeds)
    print(f"\n\tTitle: {title}\n")
    for row in mapping_arr:
        print(row)
        seeds = apply_mapping(row, new_seeds)
    print(seeds)
print(min(seeds))


# not 311025940
# 311025940



# seeds: 79 14 55 13

# seed-to-soil map:
# 50 98 2
# 52 50 48

# source category to destination category

# destination range start, source range start, range length

# 50 98 2

# dst range start 50
# src range start 98
# range length 2
# dst range == 50, 51
# src range == 98, 99

# 52 50 48
# dst range start 52
# src range start 50
# range length 48
# dst range == 52, 53, 54, 55...96, 97, 98, 99
# src range == 50, 51, 52, 53...94, 95, 96, 97

# Seed number 79 corresponds to soil number 81.
# Seed number 14 corresponds to soil number 14.
# Seed number 55 corresponds to soil number 57.
# Seed number 13 corresponds to soil number 13.

# [82, 43, 86, 35]

# [81, 53, 57, 52]
# fertilizer-to-water map:
# 49 53 8
# 0 11 42
# 42 0 7
# 57 7 4

# SRC Range: 53 - 60
# DST Range: 49 - 56
# 81 81
# 53 49
# 57 53
# 52 52

# SRC Range: 11 - 52
# DST Range: 0 - 41
# 81 81
# 49 39
# 53 53
# 52 41

# SRC Range: 0 - 6
# DST Range: 42 - 48