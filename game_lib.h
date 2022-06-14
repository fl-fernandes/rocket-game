#ifndef __GAME_LIB_OBJ__
#define __GAME_LIB_OBJ__

#include <SDL2/SDL.h>
#include <cinttypes>
#include "vector.h"

#define RGB_MAX_VALUE   (255)
#define RGB_MIN_VALUE   (0)
#define ALPHA_MAX_VALUE (1.0f)
#define ALPHA_MIN_VALUE (0.0f)

#define WIN_WIDTH  (800)
#define WIN_HEIGHT (600)

using namespace game_t;

namespace game_t
{
	using coord_t = float;	
	using spectre_t = uint8_t;
	using point_t = vector_t;
	
	void render_objs (yadsl::vector_t objects);
	
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
	
	class object_t
	{	
		private:
			point_t pos;
			color_t color;
			hitbox_t hitbox;
			vector_t speed;
		
		public:
			inline point_t::vector_t get_posx ()
			{
				return this->pos.x;
			}
			
			inline void set_posx (vector_t x)
			{	
				this->pos.x = x;
			}
			
			inline point_t::vector_t get_posy ()
			{
				return this->pos.y;
			}
			
			inline void set_posy (vector_t y)
			{	
				this->pos.y = y;
			}
			
			inline color_t::spectre_t get_r ()
			{
				return this->color.r;
			}
			
			inline void set_r (spectre_t r)
			{	
				this->color.r = r;
			}
			
			inline color_t::spectre_t get_g ()
			{
				return this->color.g;
			}
			
			inline void set_g (spectre_t g)
			{	
				this->color.g = g;
			}
			
			inline color_t::spectre_t get_b ()
			{
				return this->color.b;
			}
			
			inline void set_b (spectre_t b)
			{	
				this->color.b = b;
			}
			
			inline color_t::spectre_t get_a ()
			{
				return this->color.a;
			}
			
			inline void set_r (spectre_t a)
			{	
				this->color.a = a;
			}
			
			inline void set_rgb (spectre_t r, spectre_t g, spectre_t b, spectre_t a)
			{
				this->color.r = r;
				this->color.g = g;
				this->color.b = b;
				this->color.a = a; 
			}
			
			inline hitbox_t::coord_t get_height ()
			{
				return this->hitbox.h;
			}
			
			inline void set_height (coord_t h)
			{
				this->hitbox.h = h;
			}
			
			inline hitbox_t::coord_t get_width ()
			{
				return this->hitbox.w;
			}
			
			inline void set_width (coord_t w)
			{
				this->hitbox.w = w;
			}
			
			inline vector_t::coord_t get_speedx ()
			{
				return this->speed.x;
			}
			
			inline vector_t::coord_t set_speedx (vector_t x)
			{
				this->speed.x = x;
			}
			
			inline vector_t::coord_t get_speedy ()
			{
				return this->speed.y;
			}
			
			inline vector_t::coord_t set_speedy (vector_t y)
			{
				this->speed.y = y;
			}
	};
}

#endif

