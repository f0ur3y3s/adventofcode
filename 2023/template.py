import os
import argparse

ROOT = os.path.dirname(os.path.abspath(__file__))

def parse_file(filename):
    with open(os.path.join(ROOT, filename), "r") as file:
        raw_data = file.read()
    return raw_data

def main(filename):
    data = parse_file(filename)
    pass


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("filename", help="input file")
    args = parser.parse_args()
    if not args.filename:
        print("Missing input file")
        exit(1)
    main(args.filename)