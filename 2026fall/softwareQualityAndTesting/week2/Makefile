CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
TARGET = number_converter

all: $(TARGET)

$(TARGET): number_converter.c
	$(CC) $(CFLAGS) number_converter.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
