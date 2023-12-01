CC=gcc
CFLAGS=-I.
SRC_NAME=part2
DEPS = $(SRC_NAME).c
OBJ = $(SRC_NAME).o
EXECUTABLE=$(SRC_NAME)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $(EXECUTABLE) $^ $(CFLAGS)

run: all
	./$(EXECUTABLE) input.txt

test: all
	./$(EXECUTABLE) test.txt

clean:
	rm -f $(OBJ) $(EXECUTABLE)