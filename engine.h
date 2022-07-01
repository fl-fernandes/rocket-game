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

#define RGB_MAX_VALUE   (255)
#define RGB_MIN_VALUE   (0)
#define ALPHA_MAX_VALUE (1.0f)
#define ALPHA_MIN_VALUE (0.0f)

namespace game_t
{
	using namespace game_t;

	using coord_t = float;	
	using spectre_t = uint32_t;
	
	struct hitbox_t
	{ 
		coord_t w;
		coord_t h;
		
		hitbox_t () {}
		
		hitbox_t (coord_t width, coord_t height)
		{
			this->w = width;
			this->h = height;
		}
	};

	struct vector_t 
	{
		coord_t x;
		coord_t y;
		
		vector_t () {}
		
		vector_t (coord_t x, coord_t y)
		{
			this->x = x;
			this->y = y;
		}
	};

	using point_t = vector_t;

	struct color_t
	{	
		char hex[8];
		spectre_t r;
		spectre_t g;
		spectre_t b;
		spectre_t a;
		
		color_t () {}
		
		color_t (spectre_t red, spectre_t green, spectre_t blue, spectre_t alpha = ALPHA_MAX_VALUE)
		{
			this->r = red;
			this->g = green;
			this->b = blue;
			this->a = alpha;
			std::snprintf(this->hex, sizeof this->hex, "#%02x%02x%02x", red, green, blue);
		}

		color_t (const char *hex, spectre_t alpha = ALPHA_MAX_VALUE)
		{
			strcpy(this->hex, hex);
			std::sscanf(hex, "#%02x%02x%02x", &this->r, &this->g, &this->b);
			this->a = alpha;
		}
	};
	
	class object_t
	{	
		private:
			SDL_Texture *texture = nullptr;

		protected:
			hitbox_t hitbox;
			point_t position;
			vector_t velocity;
			color_t color;

		GETTER_SETTER_REF(hitbox_t, hitbox);
		GETTER_SETTER_REF(point_t, position);
		GETTER_SETTER_REF(vector_t, velocity);
		GETTER_SETTER_REF(color_t, color);
		OO_ENCAPSULATE(std::string, texture_path);
		OO_ENCAPSULATE_DV(bool, show_hitbox, true);

		public:
			~object_t();
			object_t() {}
			object_t(
				const hitbox_t &hitbox, 
				const point_t &position, 
				const color_t &color
			);
			object_t(
				const hitbox_t &hitbox, 
				const point_t &position, 
				const color_t &color, 
				const char *texture_path
			);

		public:
			inline SDL_Texture* get_texture()
			{
				return this->texture;
			} 
			inline float get_area()
			{
			return this->hitbox.w * this->hitbox.h;
			}
			inline point_t get_tlcorner ()
			{
				return point_t(this->position.x, this->position.y);
			}
			inline point_t get_blcorner ()
			{
				return point_t(this->position.x, (this->position.y + this->hitbox.h));
			}
			inline point_t get_trcorner ()
			{
				return point_t((this->position.x + this->hitbox.w), this->position.y);
			}
			inline point_t get_brcorner ()
			{
				return point_t(this->get_trcorner().x, this->get_blcorner().y);
			}

		public:
			bool load_texture();
			virtual void handle_collision (object_t& object) {};
	};

	using objects_allocator_type = yadsl::vector_t<object_t*>;

	enum class motion_direction_t
	{
		up,
		down,
		left,
		right,
		up_right,
		up_left,
		down_right,
		down_left,
	};

	extern std::function<void(SDL_Event&, float)> handle_event;
	void init (const char* game_name, uint32_t screen_width, uint32_t screen_height, objects_allocator_type *objects);
	void end ();
	static void render_objs ();
	void run (std::function<void(float)> game_loop);
	void pause ();
	void unpause ();
	bool is_paused ();

	// uniform rectilinear motion
	void urm (object_t& object, const float velocity, motion_direction_t direction);
	// uniform variable rectilinear motion
	void uvrm (object_t& object, const float acceleration, motion_direction_t direction);
}

#endif

