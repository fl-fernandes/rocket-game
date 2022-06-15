HEADERS = $(wildcard *.h)
CPPS = $(wildcard *.cpp)

all: rocket-game

rocket-game: $(CPPS) $(HEADERS)
	g++ -o rocket-game $(CPPS) `pkg-config --cflags --libs sdl2`
