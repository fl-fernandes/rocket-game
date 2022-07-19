#include "game.h"
#include "mountain.h"

using namespace engine;

float gravity = 20.0f;
vector_t wind_force(500.0f, -200.0f);

music_t main_music_theme("./audios/main-theme-mu.wav");

objects_allocator_type objects(100);
texts_allocator_type texts(20);

orbiter_t player(
	hitbox_t(40, 56.1),
	point_t(100, 50),
	color_t("#9649e3"),
	24310.0f,
	"./textures/orbiter.bmp"
);

object_t thruster(
	hitbox_t(40, 20),
	point_t(100, 106.1),
	color_t("#9649e3"),
	1.0f,
	"./textures/thruster-fire.bmp"
);

ui_text_t fps(
	hitbox_t(60, 15),
	point_t(SCREEN_WIDTH - 70, 10),
	color_t("#1eba47"),
	"./textures/font.ttf",
	"",
	8
);

ui_text_t gravity_info(
	hitbox_t(170, 20),
	point_t(10, 10),
	color_t("#e86500"),
	"./textures/font.ttf",
	"",
	8
);

ui_text_t wind_force_info(
	hitbox_t(470, 20),
	point_t(10, 40),
	color_t("#e80078"),
	"./textures/font.ttf",
	"",
	8
);

ui_text_t orbiter_mass_info(
	hitbox_t(250, 20),
	point_t(10, 80),
	color_t("#e80078"),
	"./textures/font.ttf",
	"",
	8
);

ui_text_t orbiter_speed_info(
	hitbox_t(470, 20),
	point_t(10, 110),
	color_t("#e80078"),
	"./textures/font.ttf",
	"",
	8
);

void hud (float gravity, vector_t& wind_force, orbiter_t& player)
{
	std::string gravity_message = "Gravity: " + std::to_string(gravity) + " m/s^2";
	std::string wind_force_message = "Wind force: " + std::to_string(wind_force.x) + "N" + " | " + std::to_string(wind_force.y) + "N";
	std::string orbiter_mass_message = "Orbiter mass: " + std::to_string(player.get_mass()) + " Kg";
	std::string orbiter_speed_message = "Orbiter speed: " + std::to_string(player.get_velocity().x) + " Km/h" + " | " + std::to_string(player.get_velocity().y) + " Km/h";

	gravity_info.set_message(gravity_message.c_str(), get_renderer());
	wind_force_info.set_message(wind_force_message.c_str(), get_renderer());
	orbiter_mass_info.set_message(orbiter_mass_message.c_str(), get_renderer());
	orbiter_speed_info.set_message(orbiter_speed_message.c_str(), get_renderer());
}

int main(int argc, char **argv)
{
	texts.push(&fps);
	texts.push(&gravity_info);
	texts.push(&wind_force_info);
	texts.push(&orbiter_mass_info);
	texts.push(&orbiter_speed_info);

	objects.push(&player);
	objects.push(&thruster);
	mountains(objects);

	thruster.set_render(false);
	player.set_thruster_object(&thruster);

	init(
		"Father Junior ThunderMouth, The Truly And Only",
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		&objects,
		&texts,
		false
    );
    
    load_background("./textures/bg.bmp");
	main_music_theme.play();

	handle_event = [&] (SDL_Event& e, float time) {
    	player.handle_event(e, gravity, time);
    };

   	run([&] (float elapsed) {
		fps.set_message(std::to_string(get_fps()).c_str(), get_renderer());
		player.physics(gravity, wind_force, elapsed);
		hud(gravity, wind_force, player);
    });

    return 0;
}
