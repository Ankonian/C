CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = sorting.o bv.o minSort.o bubbleSort.o insertionSort.o quickSort.o mergeSort.o

.PHONY: all
all: sorting
sorting: $(OBJECTS)
	$(CC)	$(CFLAGS) $(OBJECTS) -o sorting -lm

sorting.o: sorting.c
	$(CC)	$(CFLAGS) -g -c sorting.c -lm
bv.o: bv.c
	$(CC)	$(CFLAGS) -g -c bv.c -lm
minSort.o: minSort.c
	$(CC)	$(CFLAGS) -g -c minSort.c -lm
bubbleSort.o: bubbleSort.c
	$(CC)	$(CFLAGS) -g -c bubbleSort.c -lm
insertionSort.o: insertionSort.c
	$(CC)	$(CFLAGS) -g -c insertionSort.c -lm
quickSort.o: quickSort.c
	$(CC)	$(CFLAGS) -g -c quickSort.c -lm
mergeSort.o: mergeSort.c
	$(CC)	$(CFLAGS) -g -c mergeSort.c -lm



.PHONY: clean
clean:
	rm -f	$(OBJECTS) sorting
