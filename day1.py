import os

root = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
file_name = "day1.txt"
target = os.path.join(root, file_name)

prev = -9999
counter = 1
increasing = 0
decreasing = 0
nochange = 0

with open(target) as f:
    for line in f:
        if line not in ['\n', '\r\n']:
            curr = int(line.rstrip())
            if counter == 1:
                prev = curr
                pass
            if curr > prev:
                increasing += 1

            prev = curr
            counter += 1

print(f"increasing: {increasing}")#, decreasing, nochange)
# 1461 is too low
# 1800? is too high