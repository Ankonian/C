CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = arraylist.o

.PHONY: all
all: arraylist
arraylist: $(OBJECTS)
	$(CC)	$(CFLAGS) -o arraylist arraylist.c -lm

arraylist.o: arraylist.c
	$(CC)	$(CFLAGS) -c arraylist.c -lm

.PHONY: clean
clean:
	-rm -f	$(OBJECTS)
