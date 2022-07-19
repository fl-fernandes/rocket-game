#ifndef __GAME_ORBITER__
#define __GAME_ORBITER__

#include "engine/engine.h"
#include "game.h"
#include "mountain.h"

using namespace engine;

class orbiter_t : public object_t 
{
	private:
		bool collided = false;
		object_t *thurster_obj = nullptr; 

	OO_ENCAPSULATE_DV(bool, destroyed, false);

	public:
		orbiter_t () : object_t() {}
		orbiter_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			float mass
		) : object_t(hitbox, position, color, mass) {}
		orbiter_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			float mass,
			const char *texture_path
		) : object_t(hitbox, position, color, mass, texture_path) {}

	public:
		void handle_event (SDL_Event& e, float gravity, float time);
		void physics (float gravity, const vector_t& wind_force, float time);
		void activate_thruster (float gravity, float force);
		void activate_side_thruster (const vector_t& thrust_force);
		void handle_object_collision (const object_t& object) override;
		void handle_wside_collision (const window_side_t& wside) override;

	public:
		inline void set_thruster_object (object_t *obj)
		{
			this->thurster_obj = obj;
		}
};

#endif
