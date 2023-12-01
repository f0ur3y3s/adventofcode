CC=gcc
CFLAGS=-I.
DEPS = part2.c
OBJ = part2.o
EXECUTABLE=part2

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