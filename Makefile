HEADERS = $(wildcard *.h)
CPPS = $(wildcard *.cpp)
ENGINE_HEADERS = $(wildcard engine/*.h)
ENGINE_CPPS = $(wildcard engine/*.cpp)

all: land-the-orbiter

land-the-orbiter: $(ENGINE_HEADERS) $(ENGINE_CPPS) $(CPPS) $(HEADERS)
	g++ -o land-the-orbiter $(ENGINE_CPPS) $(CPPS) `pkg-config --cflags --libs sdl2 SDL2_mixer SDL2_ttf`
	
O2: $(ENGINE_HEADERS) $(ENGINE_CPPS) $(CPPS) $(HEADERS)
	g++ -o land-the-orbiter $(ENGINE_CPPS) $(CPPS) -O2 `pkg-config --cflags --libs sdl2 SDL2_mixer SDL2_ttf`

clean:
	rm -f land-the-orbiter


