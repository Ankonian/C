CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = increment.o

.PHONY: all
all: increment
increment: $(OBJECTS)
	$(CC)	$(CFLAGS) $(OBJECTS) -o increment -lpthread

increment.o: increment.c
	$(CC)	$(CFLAGS) -g -c increment.c -lpthread


.PHONY: clean
clean:
	rm -f	$(OBJECTS) increment
