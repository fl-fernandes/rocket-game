#ifndef __GAME_CANNON__
#define __GAME_CANNON__

#include "engine/engine.h"
#include "game.h"

using namespace engine;

class cannon_t : public object_t
{
	
	public:
		cannon_t () {};
		cannon_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			float mass
		);
		cannon_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			float mass,
			const char *texture_path		
		);
	
	public:
		void shoot ();
};

#endif
