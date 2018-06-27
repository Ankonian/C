CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror -std=c99 -g
OBJECTS = assetManagement.o

.PHONY: all
all: assetManagement
assetManagement: $(OBJECTS)
	$(CC)   $(CFLAGS) $(OBJECTS) -o increment

assetManagement.o: assetManagement.c
	$(CC)   $(CFLAGS) -g -c assetManagement.c 


.PHONY: clean
clean:
	rm -f   $(OBJECTS) assetManagement
