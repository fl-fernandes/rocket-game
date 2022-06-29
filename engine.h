#ifndef __ENGINE__
#define __ENGINE__

#include <SDL2/SDL.h>
#include <functional>
#include <cinttypes>
#include <chrono>
#include "vector.h"
#include "lib.h"

#define RGB_MAX_VALUE   (255)
#define RGB_MIN_VALUE   (0)
#define ALPHA_MAX_VALUE (1.0f)
#define ALPHA_MIN_VALUE (0.0f)

#define EARTH_GRAVITY_ACCLR (9.807f)

namespace game_t
{
	using namespace game_t;

	using coord_t = float;	
	using spectre_t = uint8_t;
	
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
		}
	};
	
	enum class collision_direction_t
	{
		left,
		top,
		right,
		bottom,
	};
	
	class object_t
	{	
		protected:
			hitbox_t hitbox;
			point_t position;
			vector_t velocity;
			color_t color;
			bool collided;

		GETTER_SETTER_REF(hitbox_t, hitbox);
		GETTER_SETTER_REF(point_t, position);
		GETTER_SETTER_REF(vector_t, velocity);
		GETTER_SETTER_REF(color_t, color);
		GETTER_SETTER_REF(bool, collided);

		public: 
			object_t () {}
			object_t (const hitbox_t& hitbox, const point_t& position, const color_t& color);
	
		public:
			inline float get_area ()
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
				return point_t(
					(this->position.x + this->hitbox.w), 
					(this->position.y + this->hitbox.h)
				);
			}

		public:
			virtual bool handle_collision (object_t object, collision_direction_t direction);
	};

	using objects_allocator_type = yadsl::vector_t<object_t*>;

	extern std::function<void(SDL_Event&, float)> handle_event;
	void init (const char* game_name, uint32_t screen_width, uint32_t screen_height, objects_allocator_type *objects);
	void end ();
	static void render_objs ();
	void run (std::function<void(float)> game_loop);

	float calc_free_fall_speed (float gravity_accrl);
	inline float calc_free_fall_speed (float gravity_accrl, float time);
}

#endif

