#ifndef __ROCKET_GAME__
#define __ROCKET_GAME__

#include <SDL2/SDL.h>
#include <iostream>
#include "game_lib.h"

#define SCREEN_WIDTH (1366)
#define SCREEN_HEIGHT (720)

using namespace game_t;

extern objects_allocator_type objects;

class rocket_t : public object_t 
{
	private:
		bool collided = false;

	private:
		bool check_collision ();

	public:
		rocket_t () : object_t() {}
		rocket_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color
		) : object_t(hitbox, position, color) {}
	
		void handle_event (SDL_Event& e, float time);
		void physics (float time);
};

class mountain_t : public object_t 
{
	public:
		mountain_t () {}

		mountain_t (const hitbox_t& hitbox);
};

#endif