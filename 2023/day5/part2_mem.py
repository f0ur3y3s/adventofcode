import numpy as np

def parse_data(filename):
    with open(filename, "r") as file:
        raw_data = file.read()

    sections = [section.strip() for section in raw_data.strip().split("\n\n")]
    data = {}

    for section in sections:
        lines = section.split("\n")
        title = lines[0].strip(":")
        raw_data_lines = [line.split() for line in lines[1:]]
        raw_data = np.array([[int(value) for value in row] for row in raw_data_lines])
        data[title] = raw_data

    return data

def apply_mapping(mapping_arr, seeds):
    changed_idx = set()

    for mapping in mapping_arr:
        dst_start, src_start, range_len = mapping
        src_end = src_start + range_len
        dst_end = dst_start + range_len

        condition = np.logical_and(seeds >= src_start, seeds < src_end)
        condition = np.logical_and(condition, np.logical_not(np.isin(np.arange(len(seeds)), list(changed_idx))))

        indices_to_update = np.where(condition)[0]

        seeds[indices_to_update] = dst_start + (seeds[indices_to_update] - src_start)
        changed_idx.update(indices_to_update)

    return seeds

def gen_seed_ranges(seeds):
    new_seeds = []
    seed_starts = seeds[::2]
    seed_ranges = seeds[1::2]

    for seed_start, seed_range in zip(seed_starts, seed_ranges):
        seed_range_values = np.arange(seed_start, seed_start + seed_range)
        new_seeds.extend(tqdm(seed_range_values, desc=f"{seed_start} - {seed_start + seed_range}"))

    return new_seeds

data = parse_data("input.txt")
seeds = data["seeds"][0]
data.pop("seeds", None)



for title, mapping_arr in data.items():
    seeds = apply_mapping(mapping_arr, seeds)

print(np.min(seeds))
