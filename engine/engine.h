#ifndef __ENGINE__
#define __ENGINE__

#include <SDL2/SDL.h>
#include <functional>
#include <cinttypes>
#include <cstring>
#include <string>
#include <chrono>
#include "vector.h"
#include "lib.h"

#include "physics.h"
#include "object.h"

namespace engine
{	
	using objects_allocator_type = yadsl::vector_t<engine::object_t*>;

	extern std::function<void(SDL_Event&, float)> handle_event;

	void init (const char *game_name, uint32_t screen_width, uint32_t screen_height, objects_allocator_type *objects);
	void end ();
	void run (std::function<void(float)> game_loop);
	
	bool load_background (const char *path);
	void pause ();
	void unpause ();
	bool is_paused ();
    SDL_Renderer* get_renderer ();
    float get_elapsed ();
}

#endif