CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = os_shell

all: $(TARGET)

$(TARGET): os_shell.c
	$(CC) $(CFLAGS) os_shell.c -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
