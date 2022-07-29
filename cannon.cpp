#include "cannon.h"

cannon_t::cannon_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color,
		float mass
	) : cannon_t(hitbox, position, color, mass, nullptr) {}

cannon_t::cannon_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color, 
		float mass,
		const char *texture_path
	) : object_t(hitbox, position, color, mass, texture_path) {}

void cannon_t::shoot()
{
	object_t *projectile = new object_t(
		hitbox_t(20, 20),
		point_t(1190, 500),
		color_t("#ffffff"),
		100.0f,
		""
	);
	
	projectile->get_velocity() = vector_t(-100, -10);
	
	objects.push(projectile);
}
