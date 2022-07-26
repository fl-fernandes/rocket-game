#include "game.h"
#include "mountain.h"

using namespace engine;

float gravity = 20.0f;

//amount of fuel in liters
float total_fuel = 5000.0f; 

vector_t wind_force(500.0f, -200.0f);

music_t main_music_theme("./audios/main-theme-mu.wav");

objects_allocator_type objects(100);
texts_allocator_type texts(20);

orbiter_t player(
	hitbox_t(40, 56.1),
	point_t(100, 50),
	color_t("#9649e3"),
	24310.0f,
	total_fuel,
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

ui_text_t orbiter_fuel_info(
	hitbox_t(250, 20),
	point_t(10, 140),
	color_t("#e80078"),
	"./textures/font.ttf",
	"",
	8
);

ui_text_t low_orbiter_fuel(
	hitbox_t(250, 20),
	point_t(10, 140),
	color_t("#ff0000"),
	"./textures/font.ttf",
	"",
	8
);


void hud (float gravity, vector_t& wind_force, orbiter_t& player)
{
	char buffer[255];
	bool r;
	
	sprintf(buffer, "Gravity: %.2f m/s^2", gravity);
	r = gravity_info.set_message(buffer, get_renderer());
	assert(r);
	
	sprintf(buffer, "Wind force: %.2f N | %.2f N", wind_force.x, wind_force.y);
	r = wind_force_info.set_message(buffer, get_renderer());
	assert(r);
	
	sprintf(buffer, "Orbiter mass: %.2f Kg", player.get_mass());
	r = orbiter_mass_info.set_message(buffer, get_renderer());
	assert(r);
	
	sprintf(buffer, "Orbiter speed: %.2f Km/h | %.2f Km/h", player.get_velocity().x, player.get_velocity().y);
	r = orbiter_speed_info.set_message(buffer, get_renderer());
	
	sprintf(buffer, "Remaining fuel: %.2f", (player.get_fuel()/total_fuel) * 100);
	if ((player.get_fuel()/total_fuel) * 100 < 10){
		r = low_orbiter_fuel.set_message(buffer, get_renderer());
	} else {
		r = orbiter_fuel_info.set_message(buffer, get_renderer());
	}
	
	
	assert(r);
}

int main(int argc, char **argv)
{
	texts.push(&fps);
	texts.push(&gravity_info);
	texts.push(&wind_force_info);
	texts.push(&orbiter_mass_info);
	texts.push(&orbiter_speed_info);
	texts.push(&orbiter_fuel_info);
	texts.push(&low_orbiter_fuel);

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
		true
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
