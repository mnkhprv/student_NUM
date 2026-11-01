.PHONY: all run6 run7 run8 run9 run-bonus run-all clean

all: task6 task7 task8 task9 bonus
	@echo "Compiled all programs."
	@echo "Run one with: make run6, run7, run8, run9, or run-bonus"

task6: src/task6_decimal_to_binary.cpp
	g++ src/task6_decimal_to_binary.cpp -o task6

task7: src/task7_negative_to_binary.cpp
	g++ src/task7_negative_to_binary.cpp -o task7

task8: src/task8_add.cpp
	g++ src/task8_add.cpp -o task8

task9: src/task9_multiply.cpp
	g++ src/task9_multiply.cpp -o task9

bonus: src/bonus_divide.cpp
	g++ src/bonus_divide.cpp -o bonus

run6: task6
	./task6

run7: task7
	./task7

run8: task8
	./task8

run9: task9
	./task9

run-bonus: bonus
	./bonus

run-all: all
	./task6
	./task7
	./task8
	./task9
	./bonus

clean:
	rm -f task6 task7 task8 task9 bonus
