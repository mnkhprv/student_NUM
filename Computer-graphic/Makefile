CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic
CC := gcc
CFLAGS := -Wall -Wextra -pedantic
LDLIBS := -lglut -lGLU -lGL
SOURCES := $(wildcard lab*/main.cpp)
RUN_TARGETS := $(addprefix run-,$(SOURCES))

.PHONY: clean $(RUN_TARGETS)

$(RUN_TARGETS): run-%: %
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$(wildcard $(dir $*)*.cpp)) $(filter %.c,$(wildcard $(dir $*)*.c)) -o $(dir $*)$(basename $(notdir $*)) $(LDLIBS)
	./$(dir $*)$(basename $(notdir $*))

clean:
	rm -f $(foreach src,$(SOURCES),$(dir $(src))$(basename $(notdir $(src))))
