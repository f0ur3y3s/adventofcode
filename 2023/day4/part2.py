def check_cards():
    for c, card in enumerate(cards):
        count, winning, mine = card
        in_both = winning & mine
        matches = len(in_both)
        if matches == 0:
            continue

        for cc in range(c + 1, c + 1 + matches):
            cards[cc][0] += count
    return


def count_cards():
    count = 0
    for card in cards:
        count += card[0]
    return count


filename = "input.txt"
# filename = "test.txt"

with open(filename) as file:
    input = file.read().splitlines()
    # input = file.readlines()
cards = [
    [
        1,
        set(line.replace(":", "|").split("|")[1].split()),
        set(line.replace(":", "|").split("|")[2].split()),
    ]
    for line in input
]

check_cards()

total_cards = count_cards()

print()
print("Total cards:", total_cards)
