#include "engine.h"

namespace game_t 
{
	using namespace game_t;

	std::function<void(SDL_Event&, float)> handle_event = nullptr;
	static uint32_t screen_width;
	static uint32_t screen_height;
	static SDL_Window *window;
	static SDL_Renderer *renderer;
	static yadsl::vector_t<object_t*> *objects;
	static float elapsed = .0f;
	static bool initialized = false;
	static bool running = false;
	
	object_t::object_t (const hitbox_t& hitbox, const point_t& position, const color_t& color) 
	{
		this->position = position;
		this->hitbox = hitbox;
		this->color = color;
		this->velocity = vector_t(0, 0);
	}
	
	bool object_t::handle_collision (object_t object, collision_direction_t direction)
	{
		return false;
	}

	void init (
		const char* game_name, 
		uint32_t screen_width, 
		uint32_t screen_height, 
		objects_allocator_type *objs
	)
	{
		game_t::screen_width = screen_width;
		game_t::screen_height = screen_height;
		
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			DPRINT("SDL cout not be initialize! SDL_Error: ");
			DPRINTLN(SDL_GetError());
			return;
		}

		window = SDL_CreateWindow(
			game_name,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			screen_width,
			screen_height,
			SDL_WINDOW_SHOWN
		);

		if (window == nullptr) {
			DPRINT("Window could not be created! SDL_Error: ");
			DPRINTLN(SDL_GetError());
			return;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (renderer == nullptr) {
			DPRINT("Renderer could not be created! SDL_Error: ");
			DPRINTLN(SDL_GetError());
			return;
		}

		objects = objs;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		initialized = true;
	}

	void close ()
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		window = nullptr;
		renderer = nullptr;
		elapsed = .0f;
		SDL_Quit();
	}

	static void render_objs ()
	{
		SDL_Rect rect;

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		objects_allocator_type& objs = *objects;

		for (uint32_t i = 0; i < objs.size(); i++) {
			object_t& obj = *objs[i];
			
			rect.x = obj.get_position().x;
			rect.y = obj.get_position().y;
			rect.w = obj.get_hitbox().w;
			rect.h = obj.get_hitbox().h;

			SDL_SetRenderDrawColor(
				renderer, 
				obj.get_color().r, 
				obj.get_color().g, 
				obj.get_color().b, 
				255
			);
			
			SDL_RenderFillRect(renderer, &rect);
		}

		SDL_RenderPresent(renderer);
	}

	inline static bool check_collision_on_left (object_t& obj1, object_t& obj2)
	{
		return obj1.get_position().x == obj2.get_position().x &&
			obj1.get_tlcorner().y <= obj2.get_trcorner().y &&
			obj1.get_blcorner().y >= obj2.get_trcorner().y;
	}
	
	inline static bool check_collision_on_top (object_t& obj1, object_t& obj2)
	{
		return obj1.get_position().y == obj2.get_position().y &&
			obj1.get_tlcorner().x <= obj2.get_blcorner().x &&
			obj1.get_trcorner().x >= obj2.get_blcorner().x;
	}
	
	inline static bool check_collision_on_right (object_t& obj1, object_t& obj2)
	{
		return obj1.get_position().x == obj2.get_position().x &&
			obj1.get_trcorner().y <= obj2.get_tlcorner().y &&
			obj1.get_brcorner().y >= obj2.get_tlcorner().y;
	}
	
	inline static bool check_collision_on_bottom (object_t& obj1, object_t& obj2)
	{
		return obj1.get_position().y == obj2.get_position().y &&
			obj1.get_blcorner().x <= obj2.get_tlcorner().x &&
			obj1.get_brcorner().x >= obj2.get_tlcorner().x;
	}

	static void check_collisions ()
	{
		objects_allocator_type &objs = *objects;

		for (uint i = 0; i < objs.size() - 1; i++) {
			object_t& obj_i = *objs[i];
			for (uint j = i+1; j < objs.size(); j++) {
				object_t& obj_j = *objs[j];
				bool collided = false;
				collision_direction_t direction_i;
				collision_direction_t direction_j;
				
				if (check_collision_on_left(obj_i, obj_j)) {
					collided = true;
					direction_i = collision_direction_t::left;
					direction_j = collision_direction_t::right;
				}
				else if (check_collision_on_top(obj_i, obj_j)) {
					collided = true;
					direction_i = collision_direction_t::top;
					direction_j = collision_direction_t::bottom;
				}
				else if (check_collision_on_right(obj_i, obj_j)) {
					collided = true;
					direction_i = collision_direction_t::right;
					direction_j = collision_direction_t::left;
				}
				else if (check_collision_on_bottom(obj_i, obj_j)) {
					collided = true;
					direction_i = collision_direction_t::right;
					direction_j = collision_direction_t::left;
				}
				
				if (collided) {
					obj_i.set_collided(obj_i.handle_collision(obj_j, direction_i));
					obj_j.set_collided(obj_j.handle_collision(obj_i, direction_j));
				}
			}
		}
	}

	void run (std::function<void(float)> game_loop)
	{
		if (!initialized) {
			std::cerr << "Engine must be initialized! Please, call \"init\" function to initialize" << std::endl;
			exit(1);
		}

		SDL_Event e;
		running = true;
		
		std::chrono::steady_clock::time_point tbegin, tend;

		while (running) {
			tbegin = std::chrono::steady_clock::now();
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					running = false;
					break;
				}

				if (handle_event != nullptr)
					handle_event(e, elapsed);
			}

			if (game_loop)
				game_loop(elapsed);
			
			check_collisions();

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			render_objs();

			SDL_RenderPresent(renderer);

			do {
				tend = std::chrono::steady_clock::now();
				std::chrono::duration<float> elapsed_ = std::chrono::duration_cast<std::chrono::duration<float>>(tend - tbegin);
				elapsed = elapsed_.count();
			} while (elapsed < 0.001f);
		}
		
		close();
	}

	float calc_free_fall_speed (float gravity_accrl)
	{
		return gravity_accrl * elapsed;
	}
}

