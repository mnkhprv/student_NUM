CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O3 -march=native -flto
TARGET = number_converter

all: $(TARGET)

$(TARGET): number_converter.c
	$(CC) $(CFLAGS) number_converter.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
