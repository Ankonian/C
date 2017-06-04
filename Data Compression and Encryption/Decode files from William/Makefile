CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -g
EXECS = decode encode
OBJECTS = queue.o stack.o huffman.o decode.o encode.o bv.o
SOURCES = encode.c decode.c stack.c queue.c stack.h huffman.h huffman.c code.h Makefile README bv.c bv.h

.PHONY: all
all: $(EXECS)

encode: encode.o huffman.o queue.o bv.o
	$(CC)	$(CFLAGS) encode.o huffman.o queue.o bv.o -o encode
encode.o: encode.c
	$(CC)	$(CFLAGS) encode.c
decode: decode.o huffman.o bv.o stack.o bv.o
	$(CC)	$(CFLAGS) decode.o huffman.o stack.o bv.o -o decode
decode.o: decode.c
	$(CC)	$(CFLAGS) decode.c
huffman.o: huffman.c 
	$(CC)	$(CFLAGS) -c huffman.c
stack.o: stack.c
	$(CC)	$(CFLAGS) -c stack.c
queue.o: queue.c
	$(CC)	$(CFLAGS) -c queue.c 
bv.o: bv.c
	$(CC)	$(CFLAGS) -c bv.c

.PHONY: clean
clean:
	rm -f $(EXECS) $(OBJECTS) 
