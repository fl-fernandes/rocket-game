HEADERS = $(wildcard *.h)
CPPS = $(wildcard *.cpp)
ENGINE_HEADERS = $(wildcard engine/*.h)
ENGINE_CPPS = $(wildcard engine/*.cpp)

all: rocket-game

rocket-game: $(ENGINE_HEADERS) $(ENGINE_CPPS) $(CPPS) $(HEADERS)
	g++ -o rocket-game $(ENGINE_CPPS) $(CPPS) `pkg-config --cflags --libs sdl2 SDL2_mixer SDL2_ttf`
