#include <SDL2/SDL.h>
#include <iostream>
#include "game_lib.h"

#define SCREEN_WIDTH (640)
#define SCREEN_HEIGHT (480)

using namespace game_t;

yadsl::vector_t<object_t> objs(3);

class rocket_t : public object_t 
{
	public:
		rocket_t () : object_t() {}
		rocket_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color
		) : object_t(hitbox, position, color) {}
	
		void handle_event (SDL_Event& e, float time)
		{
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						this->speed.y -= 1500 * time;
						break;
				}
			}
		}

		void physics (float time)
		{
			this->pos.y += this->speed.y * time;
			this->speed.y += calc_free_fall_speed(EARTH_GRAVITY_ACCLR);
			DPRINT("Rocket free fall speed: ");
			DPRINTLN(this->speed.y);
		}
};

auto rocket_index = objs.emplace_back(
	hitbox_t(10, 20),
	point_t(SCREEN_WIDTH / 2, 0),
	color_t(255, 0, 0, 1)
);

rocket_t& rocket = static_cast<rocket_t&>(objs.at(rocket_index));

int main(int argc, char* args[])
{
	init(
		"Father Junior ThunderMouth, The Truly And Only",
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		&objs
    );
    
    handle_event = [&] (SDL_Event& e, float time) {
    	rocket.handle_event(e, time);
    };

   	run([&] (float elapsed) {
		// rocket.move(elapsed);
		rocket.physics(elapsed);
    });

    return 0;
}
