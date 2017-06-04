CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = increment.o

.PHONY: all
all: increment
increment: $(OBJECTS)
	$(CC)	$(CFLAGS) $(OBJECTS) -o increment -lm

increment.o: gdbLab.c
	$(CC)	$(CFLAGS) -g -c increment.c -lm


.PHONY: clean
clean:
	rm -f	$(OBJECTS) increment
