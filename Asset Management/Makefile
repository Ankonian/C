CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = assetManagement.o

.PHONY: all
all: assetManagement
assetManagement: $(OBJECTS)
	$(CC)   $(CFLAGS) $(OBJECTS) -o increment -lncurses

assetManagement.o: assetManagement.c
	$(CC)   $(CFLAGS) -c assetManagement.c -lncurses


.PHONY: clean
clean:
	rm -f   $(OBJECTS) assetManagement
