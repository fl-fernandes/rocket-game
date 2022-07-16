#include "rocket_game.h"

using namespace engine;

float gravity = 20.0f;

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
				this->activate_thruster(3.0f);
				break;
			case SDLK_RIGHT:
				this->activate_side_thruster(vector_t(2000, 0));
				break;
			case SDLK_LEFT:
				this->activate_side_thruster(vector_t(-2000, 0));
				break;
		}
	}
}

void orbiter_t::activate_thruster (float force)
{
	vector_t thrust = weight_force(gravity, this->get_mass());
	thrust.y *= -force;
	this->add_to_resulting_force(thrust);
}

void orbiter_t::activate_side_thruster (const vector_t& thrust_force)
{
	this->add_to_resulting_force(thrust_force);
}

void orbiter_t::physics (float time)
{
	if (this->collided) {
		this->set_velocity(vector_t(0.0f, 0.0f));
		return;
	}

	this->add_to_resulting_force(weight_force(gravity, this->get_mass()));
	this->add_to_resulting_force(wind_drag_force(vector_t(500.0f, -200.0f), this->get_velocity()));
}

mountain_t::mountain_t (const hitbox_t& hitbox)
{
	this->set_position(point_t(0, SCREEN_HEIGHT - hitbox.h));
	this->set_color(color_t("#c7a87e"));
	this->set_hitbox(hitbox);
	this->set_mass(24.310f);
}

void mountain_t::handle_object_collision(const object_t& object)
{
	if (typeid(object) == typeid(orbiter_t))
		this->set_color(color_t("#f00"));
}

objects_allocator_type objects(20);
texts_allocator_type texts(20);

orbiter_t player(
	hitbox_t(30, 56.1),
	point_t(100, 50),
	color_t("#9649e3"),
	24310.0f,
	"./textures/orbiter.bmp"
);

ui_text_t pixel(
	hitbox_t(100, 30),
	point_t(120, 80),
	color_t(255,255,255),
	"./textures/font.ttf",
	"Teste:",
	12
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
	player.set_show_hitbox(false);

	objects.push(&player);
	texts.push(&pixel);
	generate_mountains(150, 100);

	init(
		"Father Junior ThunderMouth, The Truly And Only",
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		&objects,
		&texts
    );
    
    load_background("./textures/sky1.bmp");
	main_music_theme.play();

	handle_event = [&] (SDL_Event& e, float time) {
    	player.handle_event(e, time);
    };

   	run([&] (float elapsed) {
		player.physics(elapsed);
    });

    return 0;
}
