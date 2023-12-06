import os
import argparse

ROOT = os.path.dirname(os.path.abspath(__file__))

def parse_file(filename):
    with open(os.path.join(ROOT, filename), "r") as file:
        raw_data = file.readlines()

    time_line = raw_data[0].split()[1:]
    distance_line = raw_data[1].split()[1:]

    raw_data = [(int(time), int(distance)) for time, distance in zip(time_line, distance_line)]
    print(raw_data)
    return raw_data

def solve(race_data):
    result = 1
    for race_time, record_distance in race_data:
        win_cmbs = 0
        for button_hold_time in range(int(race_time * 1.5)):
            boat_speed = button_hold_time
            movement_duration = race_time - button_hold_time
            travel_distance = boat_speed * movement_duration
            if travel_distance > record_distance:
                win_cmbs += 1
        result *= win_cmbs
    return result


def main(filename):
    data = parse_file(filename)
    result = solve(data)
    print(result)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="input file")
    args = parser.parse_args()
    if not args.filename:
        print("Missing input file")
        exit(1)
    main(args.filename)