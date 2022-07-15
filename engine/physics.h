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
}

#endif
