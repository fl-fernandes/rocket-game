#ifndef __ENGINE_PHYSICS__
#define __ENGINE_PHYSICS__

#include "engine.h"
#include "object.h"

namespace engine
{
	inline vector_t weight_force (float gravity_acclr, float mass)
	{
		return vector_t(0.0f, gravity_acclr * mass);
	}
	vector_t wind_drag_force (const vector_t& wind_vel, vector_t& object_vel, float Cd = 1.05f);
}

#endif
