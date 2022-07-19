#ifndef __GAME_MOUNTAIN__
#define __GAME_MOUNTAIN__

#include "engine/engine.h"
#include "game.h"
#include "orbiter.h"

using namespace engine;

class mountain_t : public object_t 
{
	public:
		mountain_t () {}
		mountain_t (const hitbox_t& hitbox);

	public:
		void handle_object_collision (const object_t &object) override;
};

void mountains (objects_allocator_type& objects);

#endif