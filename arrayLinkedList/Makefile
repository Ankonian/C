CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99
CC = gcc $(CFLAGS)
EXEC = linkedListTest
OBJECTS = linkedListTest.o arrayLinkedList.o

.PHONY: all
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS)
linkedListTest.o: linkedListTest.c
	$(CC) -c linkedListTest.c
arrayLinkedList.o: arrayLinkedList.c
	$(CC) -c arrayLinkedList.c

.PHONY: clean
clean:
	rm -f $(EXEC) $(OBJECTS)
