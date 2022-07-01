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
	static bool paused = false;

	object_t::object_t(
		const hitbox_t &hitbox, 
		const point_t &position, 
		const color_t &color
	)
	{
		this->position = position;
		this->hitbox = hitbox;
		this->color = color;
		this->velocity = vector_t(0, 0);
		if (texture_path != "")
			this->set_texture_path(texture_path);
	}
	object_t::object_t(
		const hitbox_t &hitbox, 
		const point_t &position, 
		const color_t &color, 
		const char *texture_path
	) : object_t(hitbox, position, color)
	{
		this->texture_path = texture_path;
	}

	object_t::~object_t ()
	{
		if (this->texture != nullptr)
			SDL_DestroyTexture(this->texture);
	}

	bool object_t::load_texture ()
	{
		if (this->texture_path != "" && renderer != nullptr) {
			SDL_Surface *surface = SDL_LoadBMP(this->texture_path.c_str());
			if (surface == nullptr)
				return false;

			SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (texture == nullptr)
				return false;
			
			if (this->texture != nullptr)
				SDL_DestroyTexture(this->texture);
			SDL_FreeSurface(surface);
			this->texture = texture;
			return true;
		}

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

		for (uint32_t i = 0; i < objects->size(); i++)
			objects->at(i)->load_texture();

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

		objects_allocator_type& objs = *objects;

		for (uint32_t i = 0; i < objs.size(); i++) {
			object_t& obj = *objs[i];
			
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

	inline static bool check_collision (object_t& obj1, object_t& obj2)
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

				if (check_collision(obj_i, obj_j)) {
					obj_i.handle_collision(obj_j);
					obj_j.handle_collision(obj_i);
				}
			}
		}
	}

	void handle_keydown(SDL_Event &e)
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

				handle_keydown(e);

				if (handle_event != nullptr)
					handle_event(e, elapsed);
			}

			if (!paused) {
				if (game_loop)
					game_loop(elapsed);
				
				check_collisions();

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

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

	void urm (object_t& object, const float velocity, motion_direction_t direction)
	{
		if (
			direction == motion_direction_t::up || 
			direction == motion_direction_t::up_left ||
			direction == motion_direction_t::up_right
		) {
			object.get_velocity().y = (velocity * elapsed);
			object.get_position().y -= object.get_velocity().y;
		}
		else if (
			direction == motion_direction_t::down ||
			direction == motion_direction_t::down_left ||
			direction == motion_direction_t::down_right
		) {
			object.get_velocity().y = (velocity * elapsed);
			object.get_position().y += object.get_velocity().y;
		}

		if (
			direction == motion_direction_t::left || 
			direction == motion_direction_t::up_left ||
			direction == motion_direction_t::down_left
		) {
			object.get_velocity().x = (velocity * elapsed);
			object.get_position().x -= object.get_velocity().x;
		}
		else if (
			direction == motion_direction_t::right ||
			direction == motion_direction_t::up_right ||
			direction == motion_direction_t::down_right
		) {
			object.get_velocity().x = (velocity * elapsed);
			object.get_position().x += object.get_velocity().x;
		}
	}

	void uvrm (object_t& object, const float acceleration, motion_direction_t direction)
	{
		if (
			direction == motion_direction_t::up ||
			direction == motion_direction_t::up_left ||
			direction == motion_direction_t::up_right)
		{
			object.get_velocity().y += (acceleration * elapsed);
			object.get_position().y -= (object.get_velocity().y * elapsed);
		}
		else if (
			direction == motion_direction_t::down ||
			direction == motion_direction_t::down_left ||
			direction == motion_direction_t::down_right)
		{
			object.get_velocity().y += (acceleration * elapsed);
			object.get_position().y += (object.get_velocity().y * elapsed);
		}

		if (
			direction == motion_direction_t::left ||
			direction == motion_direction_t::up_left ||
			direction == motion_direction_t::down_left)
		{
			object.get_velocity().x += (acceleration * elapsed);
			object.get_position().x -= (object.get_velocity().x * elapsed);
		}
		else if (
			direction == motion_direction_t::right ||
			direction == motion_direction_t::up_right ||
			direction == motion_direction_t::down_right)
		{
			object.get_velocity().x += (acceleration * elapsed);
			object.get_position().x += (object.get_velocity().x * elapsed);
		}
	}
}

