CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
TARGET = sort

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean
