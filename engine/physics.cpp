#include "physics.h"

namespace engine
{
    void uniform_rectilinear_motion (engine::object_t& object, const float velocity, motion_direction_t direction)
    {
        if (
            direction == motion_direction_t::up || 
            direction == motion_direction_t::up_left ||
            direction == motion_direction_t::up_right
        ) {
            object.get_velocity().y = (velocity * engine::get_elapsed());
            object.get_position().y -= object.get_velocity().y;
        }
        else if (
            direction == motion_direction_t::down ||
            direction == motion_direction_t::down_left ||
            direction == motion_direction_t::down_right
        ) {
            object.get_velocity().y = (velocity * engine::get_elapsed());
            object.get_position().y += object.get_velocity().y;
        }

        if (
            direction == motion_direction_t::left || 
            direction == motion_direction_t::up_left ||
            direction == motion_direction_t::down_left
        ) {
            object.get_velocity().x = (velocity * engine::get_elapsed());
            object.get_position().x -= object.get_velocity().x;
        }
        else if (
            direction == motion_direction_t::right ||
            direction == motion_direction_t::up_right ||
            direction == motion_direction_t::down_right
        ) {
            object.get_velocity().x = (velocity * engine::get_elapsed());
            object.get_position().x += object.get_velocity().x;
        }
    }

    void uniform_variable_rectilinear_motion (engine::object_t& object, const float acceleration, motion_direction_t direction)
    {
        if (
            direction == motion_direction_t::up ||
            direction == motion_direction_t::up_left ||
            direction == motion_direction_t::up_right
        )
        {
            object.get_velocity().y += (acceleration * engine::get_elapsed());
            object.get_position().y -= (object.get_velocity().y * engine::get_elapsed());
        }
        else if (
            direction == motion_direction_t::down ||
            direction == motion_direction_t::down_left ||
            direction == motion_direction_t::down_right
        )
        {
            object.get_velocity().y += (acceleration * engine::get_elapsed());
            object.get_position().y += (object.get_velocity().y * engine::get_elapsed());
        }

        if (
            direction == motion_direction_t::left ||
            direction == motion_direction_t::up_left ||
            direction == motion_direction_t::down_left
        )
        {
            object.get_velocity().x += (acceleration * engine::get_elapsed());
            object.get_position().x -= (object.get_velocity().x * engine::get_elapsed());
        }
        else if (
            direction == motion_direction_t::right ||
            direction == motion_direction_t::up_right ||
            direction == motion_direction_t::down_right
        )
        {
            object.get_velocity().x += (acceleration * engine::get_elapsed());
            object.get_position().x += (object.get_velocity().x * engine::get_elapsed());
        }
    }
}
