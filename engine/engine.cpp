#include "engine.h"

namespace engine
{
    std::function<void(SDL_Event&, float)> handle_event = nullptr;
	static uint32_t screen_width;
	static uint32_t screen_height;
	static SDL_Window *window;
	static SDL_Renderer *renderer;
	static objects_allocator_type *objects;
	static texts_allocator_type *ui_texts;
	static float elapsed = .0f;
	static bool initialized = false;
	static bool running = false;
	static bool paused = false;
	static SDL_Texture *background_texture;

    SDL_Renderer* get_renderer ()
    {
        return renderer;
    }

    float get_elapsed ()
    {
        return elapsed;
    }

    void pause () 
	{
		paused = true;
	}

	void unpause () 
	{
		paused = false;
	}

	bool is_paused ()
	{
		return paused;
	}
	
	bool load_background (const char *path)
	{
		if (renderer != nullptr) {
			SDL_Surface *surface = SDL_LoadBMP(path);
			if (surface == nullptr)
				return false;

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr)
				return false;
			
			if (background_texture != nullptr)
				SDL_DestroyTexture(background_texture);
			SDL_FreeSurface(surface);
			background_texture = texture;
			return true;
		}

		return false;
	};
	
	static void reset_resulting_forces ()
	{
		objects_allocator_type& objs = *objects;
		for (uint32_t i = 0; i < objs.size(); i++) {
			object_t& obj = *objs[i];
			obj.set_resulting_force(vector_t());
		}
	}
	
	static void calc_obj_speed_position (object_t& object)
	{
		if (object.get_mass() == 0.0f)
			return;
		
		float ax, ay;
		
		ax = object.get_resulting_force().x / object.get_mass();
		ay = object.get_resulting_force().y / object.get_mass();
		
		// S = (S0 + V0t + At^2) / 2
		object.get_position().x = object.get_position().x + object.get_velocity().x * elapsed + (ax * elapsed * elapsed) / 2.0f;
		object.get_position().y = object.get_position().y + object.get_velocity().y * elapsed + (ay * elapsed * elapsed) / 2.0f;
		
		object.get_velocity().x = object.get_velocity().x + ax * elapsed;
		object.get_velocity().y = object.get_velocity().y + ay * elapsed;
	}

    static void render_objs ()
	{
		SDL_Rect rect;

		objects_allocator_type& objs = *objects;

		for (uint32_t i = 0; i < objs.size(); i++) {
			object_t& obj = *objs[i];

			calc_obj_speed_position(obj);

			if (!obj.get_render())
				continue;

			rect.x = obj.get_position().x;
			rect.y = obj.get_position().y;
			rect.w = obj.get_hitbox().w;
			rect.h = obj.get_hitbox().h;


			if (obj.get_show_hitbox())
				SDL_SetRenderDrawColor(
					renderer, 
					obj.get_color().r, 
					obj.get_color().g, 
					obj.get_color().b, 
					obj.get_color().a
				);
			
			SDL_RenderDrawRect(renderer, &rect);
			
			if (obj.get_texture() != nullptr)
				SDL_RenderCopy(renderer, obj.get_texture(), nullptr, &rect);
		}
	}
	
	static void render_texts ()
	{
		SDL_Rect rect;

		texts_allocator_type& texts = *ui_texts;

		for (uint32_t i = 0; i < texts.size(); i++) {
			ui_text_t& obj = *texts[i];

			if (!obj.get_render())
				continue;

			rect.x = obj.get_position().x;
			rect.y = obj.get_position().y;
			rect.w = obj.get_hitbox().w;
			rect.h = obj.get_hitbox().h;


			if (obj.get_show_hitbox())
				SDL_SetRenderDrawColor(
					renderer, 
					obj.get_color().r, 
					obj.get_color().g, 
					obj.get_color().b, 
					obj.get_color().a
				);
			
			SDL_RenderDrawRect(renderer, &rect);
			
			if (obj.get_texture() != nullptr)
				SDL_RenderCopy(renderer, obj.get_texture(), nullptr, &rect);
		}
	}

	inline static bool check_object_collision (object_t& obj1, object_t& obj2)
	{
		bool xAxis = (((obj1.get_tlcorner().x <= obj2.get_tlcorner().x) &&
						obj1.get_trcorner().x >= obj2.get_tlcorner().x) ||
					  ((obj1.get_tlcorner().x <= obj2.get_trcorner().x) &&
						obj1.get_trcorner().x >= obj2.get_trcorner().x));

		bool yAxis = (((obj1.get_tlcorner().y <= obj2.get_tlcorner().y) &&
					   obj1.get_blcorner().y >= obj2.get_tlcorner().y) ||
					  ((obj1.get_tlcorner().y <= obj2.get_blcorner().y) &&
					   obj1.get_blcorner().y >= obj2.get_blcorner().y));

		return xAxis && yAxis;
	}

	static void check_collisions ()
	{
		objects_allocator_type& objs = *objects;

		for (uint i = 0; i < objs.size() - 1; i++) {
			object_t& obj_i = *objs[i];
			for (uint j = 0; j < objs.size(); j++) {
				object_t& obj_j = *objs[j];

				if (&obj_i == &obj_j)
					continue;

				if (check_object_collision(obj_i, obj_j)) {
					obj_i.handle_object_collision(obj_j);
					obj_j.handle_object_collision(obj_i);
				}

				if (obj_i.get_tlcorner().x <= 0)
					obj_i.handle_wside_collision(window_side_t::left);
				else if (obj_i.get_trcorner().y <= 0)
					obj_i.handle_wside_collision(window_side_t::top);
				else if (obj_i.get_trcorner().x >= screen_width)
					obj_i.handle_wside_collision(window_side_t::right);
				else if (obj_i.get_blcorner().y >= screen_height)
					obj_i.handle_wside_collision(window_side_t::bottom);
			}
		}
	}

    void handle_keydown (SDL_Event& e)
	{
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
				case SDLK_ESCAPE:
					if (!is_paused())
						return pause();
					return unpause();
			}
		}
	}

    void init (
		const char *game_name, 
		uint32_t screen_width, 
		uint32_t screen_height, 
		objects_allocator_type *objs,
		texts_allocator_type *texts
	)
	{
		engine::screen_width = screen_width;
		engine::screen_height = screen_height;
		
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
			DPRINT("SDL cout not be initialize! SDL_Error: ");
			DPRINTLN(SDL_GetError());
			return;
		}

		if (Mix_Init(0) < 0) {
			DPRINT("SDL_Mixer cout not be initialize! SDL_Error: ");
			DPRINTLN(Mix_GetError());
			return;
		}

		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

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
		ui_texts = texts;
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

		for (uint32_t i = 0; i < objects->size(); i++)
			objects->at(i)->load_texture(renderer);

		for (uint32_t i = 0; i < ui_texts->size(); i++)
			ui_texts->at(i)->load_texture(renderer);
			
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
			
			reset_resulting_forces();
			
			while (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					running = false;
					break;
				}

				handle_keydown(e);

				if (handle_event != nullptr)
					handle_event(e, elapsed);
			}

			if (!paused) {
				if (game_loop)
					game_loop(elapsed);
				
				check_collisions();
				
				if (background_texture != nullptr)
					SDL_RenderCopy(renderer, background_texture, NULL, NULL);
				else
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
					
				SDL_RenderClear(renderer);
					
				if (background_texture != nullptr)
					SDL_RenderCopy(renderer, background_texture, NULL, NULL);
				else
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				
				render_texts();
				render_objs();
				
				SDL_RenderPresent(renderer);
			}

			do {
				tend = std::chrono::steady_clock::now();
				std::chrono::duration<float> elapsed_ = std::chrono::duration_cast<std::chrono::duration<float>>(tend - tbegin);
				elapsed = elapsed_.count();
			} while (elapsed < 0.001f);
		}
		
		close();
	}
}
