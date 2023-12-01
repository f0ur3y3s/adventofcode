CC=gcc
INCLUDES=-I../aoc/
CFLAGS=-Wall $(INCLUDES) -g

SRC_NAME=part1
DEPS = $(SRC_NAME).c
OBJ = $(SRC_NAME).o
EXECUTABLE=$(SRC_NAME)
SRCS_AOC = $(wildcard ../aoc/*.c)
OBJS_AOC = $(SRCS_AOC:.c=.o)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(SRC_NAME)

$(SRC_NAME): $(OBJ) $(OBJS_AOC)
	$(CC) $(CFLAGS) $@.o $(OBJS_AOC) -o $@

run: all
	./$(EXECUTABLE) input.txt

test: all
	./$(EXECUTABLE) test.txt

clean:
	rm -f $(OBJ) $(EXECUTABLE) ${OBJS_AOC}
