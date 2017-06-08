CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -g
EXECS = decode encode
XTRAS = huffmanTest queueTest stackTest checker
OBJECTS = queueTest.o queue.o stack.o stackTest.o huffman.o huffmanTest.o decode.o encode.o bv.o
SOURCES = encode.c decode.c stack.c queue.c stack.h queue.h huffman.h huffman.c code.h Makefile README bv.c bv.h

.PHONY: all
all: $(EXECS)

.PHONY: extras
extras: $(XTRAS)

encode: encode.o huffman.o queue.o bv.o
	$(CC) $(CFLAGS) encode.o huffman.o queue.o stack.o bv.o -o encode
encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c
decode: decode.o huffman.o stack.o bv.o
	$(CC) $(CFLAGS) decode.o huffman.o stack.o bv.o -o decode
decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c
huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c
bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

# EXTRAS:
huffmanTest: huffmanTest.o huffman.o stack.o
	$(CC) $(CFLAGS)  huffmanTest.o huffman.o stack.o -o huffmanTest
huffmanTest.o: huffmanTest.c
	$(CC) $(CFLAGS) -c huffmanTest.c
queueTest: queueTest.o queue.o huffman.o
	$(CC) $(CFLAGS) queueTest.o queue.o huffman.o stack.o -o queueTest
queueTest.o: queueTest.c
	$(CC) $(CFLAGS) -c queueTest.c
stackTest: stackTest.o stack.o huffman.o
	$(CC) $(CFLAGS) stackTest.o stack.o huffman.o -o stackTest
stackTest.o: stackTest.c
	$(CC) $(CFLAGS) -c stackTest.c
checker: checkFile.c
	$(CC) $(CFLAGS) checkFile.c -o checker

.PHONY: clean
clean:
	rm -f $(EXECS) $(XTRAS) $(OBJECTS)
	rm -f huffmanTest queueTest stackTest checker
ci: $(SOURCES)
	git add $(SOURCES)
	git commit
	git push
