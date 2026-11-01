.PHONY: all run clean

all: adder

adder: adder.cpp
	g++ -std=c++17 -Wall -Wextra adder.cpp -o adder

run: adder
	./adder

clean:
	rm -f adder
