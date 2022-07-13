#ifndef __ENGINE_PHYSICS__
#define __ENGINE_PHYSICS__

#include "engine.h"
#include "object.h"

namespace engine
{
    enum class motion_direction_t
    {
        up,
        down,
        left,
        right,
        up_right,
        up_left,
        down_right,
        down_left,
    };

    void uniform_rectilinear_motion (engine::object_t& object, const float velocity, motion_direction_t direction);
	void uniform_variable_rectilinear_motion (engine::object_t& object, const float acceleration, motion_direction_t direction);
	inline vector_t weight_force (float gravity_acclr, float mass)
	{
		return vector_t(0.0f, gravity_acclr * mass);
	}
}

#endif
