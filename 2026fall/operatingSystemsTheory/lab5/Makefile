CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pthread
TARGETS = hello_threads race_counter mutex_counter bank

all: $(TARGETS)

hello_threads: hello_threads.c
	$(CC) $(CFLAGS) hello_threads.c -o hello_threads

# race_counter-д optimization унтраана (-O0)
race_counter: race_counter.c
	$(CC) $(CFLAGS) -O0 race_counter.c -o race_counter

mutex_counter: mutex_counter.c
	$(CC) $(CFLAGS) mutex_counter.c -o mutex_counter

bank: bank.c
	$(CC) $(CFLAGS) bank.c -o bank

clean:
	rm -f $(TARGETS) race_tsan
