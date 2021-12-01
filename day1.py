# Day 1 part 1 and 2

import os

root = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
file_name = "day1.txt"
target = os.path.join(root, file_name)

# Part 1
print("------------part 1------------")

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
                nochange += 1
            else:
                if curr > prev:
                    increasing += 1
                elif curr < prev:
                    decreasing += 1
                else:
                    nochange += 1
            # print(f"{counter} | {prev} {curr} | {increasing} {decreasing}")

            prev = curr
            counter += 1

print(f"increasing: {increasing}\ndecreasing: {decreasing}\nno change: {nochange}")#, decreasing, nochange)
# 1461 is too low
# 1800? is too high
# 1462

# Part 2

print("------------part 2------------")
nums = [int(num.rstrip()) for num in open(target)]
p2 = sum(1 for one, two, three, four in zip(nums, nums[1:], nums[2:], nums[3:]) if one+two+three < two+three+four)
print(f"increasing: {p2}")
# 433 is too low
# 1497
# for i in  zip(nums, nums[1:], nums[2:], nums[3:]):
#     print(i)
#     (6569, 6563, 6591, 6601)
#     (6563, 6591, 6601, 6632)