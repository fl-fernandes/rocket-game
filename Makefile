HEADERS = $(wildcard *.h)

all: rocket-game

rocket-game: main.cpp $(HEADERS)
	g++ -o rocket-game main.cpp `pkg-config --cflags --libs sdl2`
