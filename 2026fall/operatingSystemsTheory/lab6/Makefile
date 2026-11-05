CC = gcc
CFLAGS = -Wall -pthread
TARGETS = deadlock safe trylock

all: $(TARGETS)

deadlock: deadlock.c
	$(CC) $(CFLAGS) deadlock.c -o deadlock

safe: safe.c
	$(CC) $(CFLAGS) safe.c -o safe

trylock: trylock.c
	$(CC) $(CFLAGS) trylock.c -o trylock

clean:
	rm -f $(TARGETS)
