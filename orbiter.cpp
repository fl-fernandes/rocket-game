#include "orbiter.h"

static sound_t explosion_sound("./audios/explosion-se.wav");

static void destroy_orbiter (
	orbiter_t& orbiter, 
	const explosion_direction_t explosion_direction
)
{
	orbiter.set_render(false);
	orbiter.set_destroyed(true);

	const char *explosion_texture_path;
	hitbox_t explosion_hitbox(30.0f, 56.1f);
	point_t explosion_position = orbiter.get_tlcorner();

	switch (explosion_direction) {
		case explosion_direction_t::left:
			explosion_texture_path = "./textures/explosion-left.bmp";
			break;
		case explosion_direction_t::right:
			explosion_texture_path = "./textures/explosion-right.bmp";
			break;
		case explosion_direction_t::bottom:
			explosion_texture_path = "./textures/explosion.bmp";
			explosion_hitbox = hitbox_t(56.1f, 30.0f);
			explosion_position = point_t(
				orbiter.get_position().x - (orbiter.get_hitbox().w / 2),
				orbiter.get_blcorner().y - explosion_hitbox.h
			);
			break;
		default:
			break;
	}

	object_t* explosion = new object_t(
		explosion_hitbox,
		explosion_position,
		color_t("#9649e3"),
		0.0f,
		explosion_texture_path
	);

	objects.emplace_back(explosion);
	explosion->load_texture(get_renderer());
	explosion_sound.play();
}

void orbiter_t::handle_object_collision (const object_t& object)
{
	if (typeid(object) == typeid(mountain_t) && !this->destroyed) {
		this->collided = true;
		if (this->velocity.y > 10.0f && !this->destroyed)
			destroy_orbiter(*this, explosion_direction_t::bottom);
	}
}

void orbiter_t::handle_wside_collision (const window_side_t& wside)
{
	if (!this->collided)
		switch (wside) {
			case window_side_t::left:
				this->collided = true;
				destroy_orbiter(*this, explosion_direction_t::left);
				break;
			case window_side_t::right:
				this->collided = true;
				destroy_orbiter(*this, explosion_direction_t::right);
				break;
			case window_side_t::bottom:
				this->collided = true;
				destroy_orbiter(*this, explosion_direction_t::bottom);
				break;
			default:
				break;
		}
}

void orbiter_t::handle_event (SDL_Event& e, float gravity, float time)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				this->activate_thruster(gravity, 3.0f);
				if (this->thurster_obj != nullptr)
					this->thurster_obj->set_render(true);
				break;
			case SDLK_RIGHT:
				this->activate_side_thruster(vector_t(500000, 0));
				break;
			case SDLK_LEFT:
				this->activate_side_thruster(vector_t(-500000, 0));
				break;
		}
	}

	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				if (this->thurster_obj != nullptr)
					this->thurster_obj->set_render(false);
				break;
		}
	}
}

void orbiter_t::activate_thruster (float gravity, float force)
{
	vector_t thrust = weight_force(gravity, this->get_mass());
	thrust.y *= -force;
	this->add_to_resulting_force(thrust);
}

void orbiter_t::activate_side_thruster (const vector_t& thrust_force)
{
	this->add_to_resulting_force(thrust_force);
}

void orbiter_t::physics (float gravity, const vector_t& wind_force, float time)
{
	if (this->collided) {
		this->set_velocity(vector_t(0.0f, 0.0f));
		return;
	}

	vector_t weight = weight_force(gravity, this->get_mass());
	vector_t wind_dg_force = wind_drag_force(wind_force, this->get_velocity());

	this->add_to_resulting_force(weight);
	this->add_to_resulting_force(wind_dg_force);

	if (this->thurster_obj != nullptr) {
		this->thurster_obj->get_position().x = (this->get_position().x + 2);
		this->thurster_obj->get_position().y = this->get_blcorner().y;
	} 
}
