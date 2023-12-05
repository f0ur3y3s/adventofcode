def apply_mapping(mapping_arr, seeds):
    new_seeds = dict(seeds)  # Create a new dictionary to store the updated key-value pairs
    for mapping in mapping_arr:
        dst_start, src_start, range_len = mapping
        src_end = src_start + range_len
        dst_end = dst_start + range_len
        src_range = set(range(src_start, src_end))
        print("-" * 50)
        print(f"SRC Range: {src_start} - {src_end - 1}")
        print(f"DST Range: {dst_start} - {dst_end - 1}")
        print(f"Seeds: {seeds}")

        for seed, mod in seeds.items():
            if mod == 0 and seed in src_range:
                translated_seed = dst_start + (seed - src_start)
                print(f"Found translation: {seed} -> {translated_seed}")
                new_seeds[translated_seed] = mod

    print(f"New seeds: {new_seeds}")
    return new_seeds

# Example usage:
mapping_arr = [(10, 0, 5), (20, 5, 5)]
seeds = {0: 0, 1: 0, 2: 0, 3: 0, 4: 0, 5: 0, 6: 0, 7: 0, 8: 0, 9: 0}
new_seeds = apply_mapping(mapping_arr, seeds)
