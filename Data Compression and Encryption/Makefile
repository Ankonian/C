CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -g 
OBJECTS = encode.o huffman.o queue.o

.PHONY: all
all: encode
encode: $(OBJECTS)
	$(CC)	$(CFLAGS) $(OBJECTS) -o encode -lm
encode.o: encode.c
	$(CC)	$(CFLAGS) -c encode.c -lm
huffman.o: huffman.c
	$(CC)	$(CFLAGS) -c huffman.c -lm
queue.o : queue.c
	$(CC)	$(CFLAGS) -c queue.c

.PHONY: clean
clean:
	rm -f	$(OBJECTS) encode
