
CXX      = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Iheader
LIBS     = -lGL -lGLU -lglut -lm -lpthread -ldl
VPATH    = src

TARGET = shagai_games

AM_SRCS = state.cpp board.cpp gameplay.cpp render.cpp input.cpp
AM_OBJS = $(AM_SRCS:.cpp=.o)

AM_HEADERS = header/types.h header/state.h header/board.h header/gameplay.h header/render.h header/input.h

.PHONY: all clean

all: $(TARGET)

# ── Link ──────────────────────────────────────────────────────
$(TARGET): main.o alag_melkhii.o $(AM_OBJS) 4berh.o back.o sound.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

# ── Compile ───────────────────────────────────────────────────
main.o: main.cpp header/alag_melkhii.h header/4berh.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

alag_melkhii.o: src/alag_melkhii.cpp header/alag_melkhii.h header/input.h header/back.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

state.o: src/state.cpp header/state.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

board.o: src/board.cpp header/board.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

gameplay.o: src/gameplay.cpp header/gameplay.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

render.o: src/render.cpp header/render.h header/back.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

input.o: src/input.cpp header/input.h header/back.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

4berh.o: src/4berh.cpp header/4berh.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

back.o: src/back.cpp header/back.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

sound.o: src/sound.cpp header/sound.h header/miniaudio.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f main.o alag_melkhii.o $(AM_OBJS) 4berh.o back.o sound.o $(TARGET)
