CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = parfait.o bv.o sieve.o

.PHONY: all
all: parfait
parfait: $(OBJECTS)
	$(CC)	$(CFLAGS) -o parfait parfait.c bv.c sieve.c -lm

parfait.o: parfait.c
	$(CC)	$(CFLAGS) -c parfait.c bv.c sieve.c -lm

.PHONY: clean
clean:
	-rm -f	$(OBJECTS)
