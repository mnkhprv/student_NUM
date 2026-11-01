CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: lab3 process1 process2 process3

lab3: Lab3.c
	$(CC) $(CFLAGS) Lab3.c -o lab3

process1: Process1.c
	$(CC) $(CFLAGS) Process1.c -o process1

process2: Process2.c
	$(CC) $(CFLAGS) Process2.c -o process2

process3: Process3.c
	$(CC) $(CFLAGS) Process3.c -o process3

clean:
	rm -f lab3 process1 process2 process3
