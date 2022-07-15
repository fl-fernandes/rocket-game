#include "physics.h"

namespace engine 
{
	vector_t wind_drag_force (const vector_t& wind_vel, vector_t& object_vel, float Cd)
	{
		vector_t vel_dif = wind_vel;
		vel_dif.subtract(object_vel);
		vector_t drag_force = vel_dif;
		drag_force.set_module(Cd * (vel_dif.get_module() * vel_dif.get_module()));
		return drag_force;
	}
}

