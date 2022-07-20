#ifndef __ROCKET_GAME__
#define __ROCKET_GAME__

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <cassert>
#include "engine/engine.h"

#define SCREEN_WIDTH (1366)
#define SCREEN_HEIGHT (720)

#define EARTH_GRAVITY (9.807f)

using namespace engine;

extern objects_allocator_type objects;

enum class explosion_direction_t
{
	left,
	right,
	bottom,
};

#endif
