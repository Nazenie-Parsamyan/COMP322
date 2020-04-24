EXECUTABLES=catcher
CC=gcc
CFLAGS=-g

all: $(EXECUTABLES)

catcher:
	$(CC) $(CFLAGS) -c catcher.c
	$(CC) $(CFLAGS) -o $@ catcher.o

clean:
	rm -f $(EXECUTABLES) catcher.o