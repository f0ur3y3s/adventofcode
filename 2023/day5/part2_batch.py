from tqdm import tqdm
import os

ROOT = os.path.dirname(os.path.abspath(__file__))


def parse_data(filename):
    # dont forget to add a new line in the input file
    with open(os.path.join(ROOT, filename), "r") as file:
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


def apply_mapping(mapping_arr, unmapped_range):
    for seed_start, seed_range in (zip(unmapped_range[::2], unmapped_range[1::2])):
        mapped_range = []
        for mapping in mapping_arr:
            dst_start = mapping[0]
            src_start = mapping[1]
            range_len = mapping[2]
            src_end = src_start + range_len
            for seed in unmapped_range:
                if seed in range(src_start, src_end):
                    translated_seed = dst_start + (seed - src_start)
                    mapped_range.append(translated_seed)
                else:
                    mapped_range.append(seed)
            # src_end = src_start + range_len
            # for seed in unmapped_range:
            #     if seed in range(src_start, src_end):
            #         translated_seed = dst_start + (seed - src_start)
            #         mapped_range.append(translated_seed)
        return mapped_range
    # changed_idx = set()

    # for mapping in tqdm(mapping_arr):
    #     dst_start = mapping[0]
    #     src_start = mapping[1]
    #     range_len = mapping[2]
    #     src_end = src_start + range_len
    #     for idx, seed in tqdm(enumerate(seed_range), desc="Processing seeds", leave=False):
    #         if (src_start <= seed < src_end) and idx not in changed_idx:
    #             translated_seed = dst_start + (seed - src_start)
    #             seed_range[idx] = translated_seed
    #             changed_idx.add(idx)
    return seed_range

def main():
    data = parse_data("test.txt")
    # data = parse_data("input.txt")
    seeds = data["seeds"][0]
    data.pop("seeds", None)

    seed_to_soil             = data["seed-to-soil map"]
    soil_to_fertilizer       = data["soil-to-fertilizer map"]
    fertilizer_to_water      = data["fertilizer-to-water map"]
    water_to_light           = data["water-to-light map"]
    light_to_temperature     = data["light-to-temperature map"]
    temperature_to_humidity  = data["temperature-to-humidity map"]
    humidity_to_location     = data["humidity-to-location map"]


    def seeds_to_location(seed_ranges):
        soil_ranges          = apply_mapping(seed_to_soil, seed_ranges)
        fertilizer_ranges    = apply_mapping(soil_to_fertilizer, soil_ranges)
        water_ranges         = apply_mapping(fertilizer_to_water, fertilizer_ranges)
        light_ranges         = apply_mapping(water_to_light, water_ranges)
        temperature_ranges   = apply_mapping(light_to_temperature, light_ranges)
        humidity_ranges      = apply_mapping(temperature_to_humidity, temperature_ranges)
        location_ranges      = apply_mapping(humidity_to_location, humidity_ranges)
        return location_ranges

    print(f"{'-'*50}\nlowest position: {min(seeds_to_location(seeds))}\n{'-'*50}\n")
# def gen_seed_ranges(seeds, data):
#     mapped_seeds = []
#     for seed_start, seed_range in (zip(seeds[::2], seeds[1::2])):
#         new_seeds = []
#         new_seeds = [*tqdm(range(seed_start, seed_start + seed_range), desc=f"{seed_start} - {seed_start + seed_range}")]
#         # for seed in tqdm(range(seed_start, seed_start + seed_range), desc=f"{seed_start} - {seed_start + seed_range}"):
#         #     new_seeds.append(seed)
#         for title, mapping_arr in (data.items()):
#             print(f"\n\tApplying: {title}\n")
#             new_seeds = (apply_mapping(mapping_arr, new_seeds))
#         mapped_seeds.append(min(new_seeds))

#     return mapped_seeds

# # print(min(batch_gen_seed_ranges(seeds)))
# seeds = (gen_seed_ranges(seeds, data))

# # for title, mapping_arr in tqdm(data.items()):
# #     # print(f"\n\tTitle: {title}\n")
# #     seeds = apply_mapping(mapping_arr, seeds)

# print(f"{'-'*50}\nlowest position: {min(seeds)}\n{'-'*50}\n")

# not 15824964


if __name__ == "__main__":
    main()