#include "rocket_game.h"

using namespace engine;

sound_t explosion_sound("./audios/explosion-se.wav");
music_t main_music_theme("./audios/main-theme-mu.wav");

void destroy_orbiter (
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
		if (this->velocity.y > 30.0f && !this->destroyed)
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
			default:
				break;
		}
}

void orbiter_t::handle_event (SDL_Event& e, float time)
{
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_UP:
				this->velocity.y -= 1000 * time;
				break;
		}
	}
}

void orbiter_t::physics (float gravity, float time)
{
	if (this->collided)
		return;

	uniform_rectilinear_motion(*this, gravity*3, motion_direction_t::right);
	uniform_variable_rectilinear_motion(*this, gravity, motion_direction_t::down);
}

mountain_t::mountain_t (const hitbox_t& hitbox)
{
	this->set_position(point_t(0, SCREEN_HEIGHT - hitbox.h));
	this->set_color(color_t("#c7a87e"));
	this->set_hitbox(hitbox);
}

void mountain_t::handle_object_collision(const object_t& object)
{
	if (typeid(object) == typeid(orbiter_t))
		this->set_color(color_t("#f00"));
}

objects_allocator_type objects(20);

orbiter_t player(
	hitbox_t(30, 56.1),
	point_t(100, 50),
	color_t("#9649e3"),
	"./textures/orbiter.bmp"
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
		mountain->get_position().x = total_width;

		objects.emplace_back(mountain);
		total_width += width;
	} while (total_width < SCREEN_WIDTH);
}

int main(int argc, char **argv)
{
	float gravity = 20.0f;

	player.set_show_hitbox(false);

	objects.push(&player);
	generate_mountains(150, 100);

	init(
		"Father Junior ThunderMouth, The Truly And Only",
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		&objects
    );
    
    load_background("./textures/sky1.bmp");
	main_music_theme.play();

	handle_event = [&] (SDL_Event& e, float time) {
    	player.handle_event(e, time);
    };

   	run([&] (float elapsed) {
		player.physics(gravity, elapsed);
    });

    return 0;
}
