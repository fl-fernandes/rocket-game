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
	OO_ENCAPSULATE(float, fuel);
	OO_ENCAPSULATE(float, zero_fuel_weight);

	public:
		orbiter_t () {};
		orbiter_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			float mass,
			float fuel
		);
		orbiter_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color,
			float mass,
			float fuel,
			const char *texture_path		
		);

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
		
	private:
		void consumpt_fuel ();
};

#endif
