#include "rocket_game.h"

using namespace game_t;

bool rocket_t::check_collision ()
{
	for (uint32_t i = 0; i < objects.size(); i++) {
		object_t* object = objects[i];
		
		if (this == object)
			continue;
		else if (check_object_collision(object))
		{
			this->pos.y = (object->get_pos().y - this->hitbox.h) + 1;
			return true;
		}
	}

	return false;
}

void rocket_t::handle_event (SDL_Event& e, float time)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				this->speed.y -= 1500 * time;
				break;
		}
	}
}

void rocket_t::physics (float time)
{
	if (!collided)
		collided = this->check_collision();
	if (collided) 
		return;

	this->pos.y += this->speed.y * time;
	this->speed.y += calc_free_fall_speed(EARTH_GRAVITY_ACCLR);
}

mountain_t::mountain_t (const hitbox_t& hitbox)
{
	this->set_pos(point_t(0, SCREEN_HEIGHT - hitbox.h));
	this->set_color(color_t(74, 74, 67));
	this->set_hitbox(hitbox);
}

objects_allocator_type objects(20);

rocket_t player(
	hitbox_t(20, 56.1),
	point_t(100, 50),
	color_t(255, 0, 0, 1)
);

mountain_t mountain(hitbox_t(SCREEN_WIDTH, 100));

void generate_mountains (uint32_t max_width, uint32_t max_height)
{
	srand(time(nullptr));
	float total_width = 0;

	do {
		coord_t width = rand() % max_width + 20;
		coord_t height = rand() % max_height + 10;


		if ((total_width + width) > SCREEN_WIDTH)
			width = SCREEN_WIDTH - total_width;

		mountain_t* mountain = new mountain_t(hitbox_t(width, height));
		mountain->get_pos().x = total_width;

		objects.emplace_back(mountain);
		total_width += width;
	} while (total_width < SCREEN_WIDTH);
}

int main(int argc, char* args[])
{
	objects.push(&player);
	generate_mountains(150, 100);

	init(
		"Father Junior ThunderMouth, The Truly And Only",
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		&objects
    );
    
    handle_event = [&] (SDL_Event& e, float time) {
    	player.handle_event(e, time);
    };

   	run([&] (float elapsed) {
		player.physics(elapsed);
    });

    return 0;
}
