import os
import argparse

ROOT = os.path.dirname(os.path.abspath(__file__))

def parse_file(filename):
    with open(os.path.join(ROOT, filename), "r") as file:
        raw_data = file.readlines()

    time_line        = "".join(raw_data[0].strip().split()[1:])
    distance_line    = "".join(raw_data[1].strip().split()[1:])

    # Concatenate the digits and convert to integers
    raw_data = [int(time_line), int(distance_line)]
    print(raw_data)
    return raw_data

def ways_to_beat_record(data):
    time, distance = data
    ways = 0

    for hold_time in range(1, time + 1):
        remaining_time = time - hold_time
        speed = hold_time
        covered_distance = speed * remaining_time

        if covered_distance > distance:
            ways += 1

    return ways

def main(filename):
    data = parse_file(filename)
    result = ways_to_beat_record(data)
    print(result)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="input file")
    args = parser.parse_args()
    if not args.filename:
        print("Missing input file")
        exit(1)
    main(args.filename)