#include <SDL2/SDL.h>
#include <iostream>
#include "game_lib.h"

using namespace game_t;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class rocket_t : public game_t::object_t 
{
	public:
		rocket_t () : game_t::object_t() {}
	
		void handle_event (SDL_Event& e)
		{
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						this->get_speed().y -= 10;
						break;
					case SDLK_DOWN:
						this->get_speed().y += 10;
						break;
					case SDLK_LEFT:
						this->get_speed().x -= 10;
						break;
					case SDLK_RIGHT:
						this->get_speed().x += 10;
						break;
					default:
						break;
				}
			}
			
			/*
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						DPRINTLN(this->get_speed().y);
						this->get_speed().y += 10;
						break;
					case SDLK_DOWN:
						this->get_speed().y -= 10;
						break;
					case SDLK_LEFT:
						this->get_speed().x += 10;
						break;
					case SDLK_RIGHT:
						this->get_speed().x -= 10;
						break;
					default:
						break;
				}
			}*/
		}
		
		void move (float elapsed)
		{
			this->get_pos().x += this->get_speed().x * elapsed;
			
			if ((this->get_pos().x < 0) || (this->get_pos().x + this->get_hitbox().w > SCREEN_WIDTH)) {
				this->get_pos().x -= this->get_speed().x * elapsed;
			}
			
			this->get_pos().y += this->get_speed().y * elapsed;
			
			if ((this->get_pos().y < 0) || (this->get_pos().y + this->get_hitbox().h > SCREEN_HEIGHT)) {
				this->get_pos().y -= this->get_speed().y * elapsed;
			}
		}
};

rocket_t rocket;

int main(int argc, char* args[])
{
	rocket.set_hitbox(game_t::hitbox_t(5, 5));
	rocket.set_pos(game_t::point_t(SCREEN_WIDTH/2, SCREEN_HEIGHT/2));
	rocket.set_color(game_t::color_t(255, 0, 0, 1));

	game_t::objects().push(&rocket);

    game_t::init(
		"Father Junior ThunderMouth, The Truly And Only",
		SCREEN_WIDTH,
		SCREEN_HEIGHT
    );
    
    game_t::handle_event = [&] (SDL_Event& e) {
    	//std::cout << "tao aqui" << std::endl;
    	rocket.handle_event(e);
    };

    game_t::run([] (float elapsed) {
		rocket.move(elapsed);
    });

    return 0;
}
