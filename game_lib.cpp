#include "game_lib.h"

static SDL_Renderer* renderer;
static yadsl::vector_t<object_t> objs;

namespace game_t 
{
	void render_objs ()
	{
		SDL_Rect rect;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (uint32_t i = 0; i < objs.size(); i++) {
			object_t& obj = objs[i];
			
			rect.x = obj.get_posx();
			rect.y = obj.get_posy();
			rect.w = obj.get_width();
			rect.h = obj.get_height();

			SDL_SetRenderDrawColor(
				renderer, 
				obj.get_r(), 
				obj.get_g(), 
				obj.get_b(), 
				255
			);
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);
	}
}

