#ifndef __ROCKET_GAME__
#define __ROCKET_GAME__

#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
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

class orbiter_t : public object_t 
{
	private:
		bool collided = false;

	OO_ENCAPSULATE_DV(bool, destroyed, false);

	public:
		orbiter_t () : object_t() {}
		orbiter_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color
		) : object_t(hitbox, position, color) {}
		orbiter_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			const char *texture_path
		) : object_t(hitbox, position, color, texture_path) {}

	public:
		void handle_event (SDL_Event& e, float time);
		void physics (float gravity, float time);
		void handle_object_collision (const object_t& object) override;
		void handle_wside_collision (const window_side_t& wside) override;
};

class mountain_t : public object_t 
{
	public:
		mountain_t () {}
		mountain_t (const hitbox_t& hitbox);

	public:
		void handle_object_collision (const object_t &object) override;
};

#endif
