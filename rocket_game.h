#ifndef __ROCKET_GAME__
#define __ROCKET_GAME__

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "engine.h"

#define SCREEN_WIDTH (1366)
#define SCREEN_HEIGHT (720)

using namespace game_t;

extern objects_allocator_type objects;

class rocket_t : public object_t 
{
	private:
		bool collided_to_mountain = false;

	public:
		rocket_t () : object_t() {}
		rocket_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color
		) : object_t(hitbox, position, color) {}
		rocket_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			const char *texture_path
		) : object_t(hitbox, position, color, texture_path) {}

	public:
		void handle_event (SDL_Event& e, float time);
		void physics (float time);
		void handle_collision (object_t& object) override;
};

class mountain_t : public object_t 
{
	public:
		mountain_t () {}
		mountain_t (const hitbox_t& hitbox);

	public:
		void handle_collision (object_t &object) override;
};

#endif
