from tqdm import tqdm

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


def apply_mapping(mapping_arr, seeds):
    changed_idx = set()
    for mapping in mapping_arr:
        dst_start = mapping[0]
        src_start = mapping[1]
        range_len = mapping[2]
        src_end = src_start + range_len
        dst_end = dst_start + range_len
        # print("-" * 50)
        # print(f"SRC Range: {src_start} - {src_end - 1}")
        # print(f"DST Range: {dst_start} - {dst_end - 1}")
        # print(f"Seeds: {seeds}")
        for idx, seed in enumerate(seeds):
            if seed in range(src_start, src_end) and idx not in changed_idx:
            # if (seed > src_start and seed <= src_end) and idx not in changed_idx:
                translated_seed = dst_start + (seed - src_start)
                seeds[idx] = translated_seed
                changed_idx.add(idx)
    # print(f"Seeds: {seeds}")
    # print("-" * 50)
    return seeds

def gen_seed_ranges(seeds):
    new_seeds = []
    for seed_start, seed_range in (zip(seeds[::2], seeds[1::2])):
        for seed in tqdm(range(seed_start, seed_start + seed_range), desc=f"{seed_start} - {seed_start + seed_range}"):
            new_seeds.append(seed)
    return new_seeds

data = parse_data("input.txt")
seeds = data["seeds"][0]
data.pop("seeds", None)

seeds = (gen_seed_ranges(seeds))

for title, mapping_arr in tqdm(data.items()):
    # print(f"\n\tTitle: {title}\n")
    seeds = apply_mapping(mapping_arr, seeds)

print(min(seeds))