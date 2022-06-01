#ifndef __GAME_LIB_OBJ__
#define __GAME_LIB_OBJ__

#include <cinttypes>

#define RGB_MAX_VALUE   (255)
#define RGB_MIN_VALUE   (0)
#define ALPHA_MAX_VALUE (1.0f)
#define ALPHA_MIN_VALUE (0.0f)

#define WIN_WIDTH  (800)
#define WIN_HEIGHT (600)

namespace game_t
{
	struct hitbox_t
	{
		using dimension_t = double; 
	
		dimension_t w;
		dimension_t h;
		
		hitbox_t () {}
		
		hitbox_t (dimension_t width, dimension_t height)
		{
			this->w = width;
			this->h = height;
		}
	};

	struct point_t 
	{
		using axis_t = double;
		
		axis_t x;
		axis_t y;
		
		point_t () {}
		
		point_t (axis_t x, axis_t y)
		{
			this->x = x;
			this->y = y;
		}
	};

	struct color_t
	{
		using spectre_t = uint8_t;
		using alpha_t = float;
		
		spectre_t r;
		spectre_t g;
		spectre_t b;
		alpha_t a;
		
		color_t () {}
		
		color_t (spectre_t red, spectre_t green, spectre_t blue, alpha_t alpha = ALPHA_MAX_VALUE)
		{
			this->r = red;
			this->g = green;
			this->b = blue;
			this->a = alpha;
		}
	};
	
	using vector_t = point_t;
	
	class object_t
	{	
		game_t::point_t pos;
		game_t::color_t color;
		game_t::hitbox_t hitbox;
		game_t::vector_t speed;
	};
}

#endif

