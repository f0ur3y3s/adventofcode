CC=gcc
INCLUDES=-I../aoc/
CFLAGS=-Wall $(INCLUDES) -g

PART1=part1
PART1_DEPS = $(PART1).c
PART1_OBJ = $(PART1).o
PART1_EXECUTABLE=$(PART1)

PART2=part2
PART2_DEPS = $(PART2).c
PART2_OBJ = $(PART2).o
PART2_EXECUTABLE=$(PART2)

SRCS_AOC = $(wildcard ../aoc/*.c) 
OBJS_AOC = $(SRCS_AOC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(PART1): $(PART1_OBJ) $(OBJS_AOC)
	$(CC) $(CFLAGS) $@.o $(OBJS_AOC) -o $@

$(PART2): $(PART2_OBJ) $(OBJS_AOC)
	$(CC) $(CFLAGS) $@.o $(OBJS_AOC) -o $@

run_part1: $(PART1)
	./$(PART1_EXECUTABLE) input.txt

run_part2: $(PART2)
	./$(PART2_EXECUTABLE) input.txt

clean:
	rm -f $(PART1_OBJ) $(PART2_OBJ) $(PART1_EXECUTABLE) $(PART2_EXECUTABLE) ${OBJS_AOC}
