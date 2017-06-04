#This Makefile a code that compiles both cat.c and hello.c at the same time without going through much hassle for the hard-working graders
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99
OBJECTS = cat.o hello.o

.PHONY: all
all: myProgram


myProgram: $(OBJECTS)
	$(CC)	$(CFLAGS) cat.o -o cat
	$(CC)	$(CFLAGS) hello.o -o hello

cat: cat.o
	$(CC)	$(CFLAGS) cat.o -o cat
cat.o: cat.c
	$(CC)	$(CFLAGS) -c cat.c
hello: hello.o
	$(CC)	$(CFLAGS) hello.o -o hello
hello.o: hello.c
	$(CC)	$(CFLAGS) -c hello.c


.PHONY: clean
clean:
	rm $(OBJECTS) cat hello
