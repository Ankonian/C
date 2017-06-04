CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror 
OBJECTS = banhammer.o bf.o aes.o ll.o hash.o

.PHONY: all
all: banhammer
banhammer: $(OBJECTS)
	$(CC)	$(CFLAGS) $(OBJECTS) -o banhammer -lm

banhammer.o: banhammer.c
	$(CC)	$(CFLAGS) -g -c banhammer.c -lm
bf.o: bf.c
	$(CC)	$(CFLAGS) -g -c bf.c -lm
aes.o: aes.c
	$(CC)	$(CFLAGS) -g -c aes.c -lm
ll.o: ll.c
	$(CC)	$(CFLAGS) -g -c ll.c -lm
hash.o: hash.c
	$(CC)	$(CFLAGS) -g -c hash.c -lm

.PHONY: clean
clean:
	rm -f	$(OBJECTS) banhammer
