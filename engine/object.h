#ifndef __ENGINE_OBJECT__
#define __ENGINE_OBJECT__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <cstring>
#include "lib.h"

#define RGB_MAX_VALUE (255)
#define RGB_MIN_VALUE (0)
#define ALPHA_MAX_VALUE (1.0f)
#define ALPHA_MIN_VALUE (0.0f)

namespace engine
{
    using coord_t = float;	
	using spectre_t = uint32_t;

	enum class window_side_t
	{
		left,
		top,
		right,
		bottom,
	};

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
		coord_t z = 0;
		
		vector_t () {
			this->x = 0.0f;
			this->y = 0.0f;
		}
		
		vector_t (coord_t x, coord_t y)
		{
			this->x = x;
			this->y = y;
		}
		
		inline void add (const vector_t& v)
		{
			this->x += v.x;
			this->y += v.y;
			this->z += v.z;
		}
		
		inline void subtract (const vector_t& v)
		{
			this->x -= v.x;
			this->y -= v.y;
			this->z -= v.z;
		}
		
		inline void multiply (coord_t n)
		{
			this->x *= n;
			this->y *= n;
			this->z *= n;
		}
		
		inline void divide (coord_t n)
		{
			this->x /= n;
			this->y /= n;
			this->z /= n;
		}
		
		static coord_t prod_int (const vector_t& v1, const vector_t& v2);
		coord_t get_module ();
		void set_module (coord_t mod);
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

	class base_object_t 
	{
		protected:
			SDL_Texture *texture = nullptr;
			hitbox_t hitbox;
			point_t position;
			color_t color;
			std::string texture_path;
			bool show_hitbox = true;
			bool render = true;

		GETTER_SETTER_REF(hitbox_t, hitbox);
		GETTER_SETTER_REF(point_t, position);
		GETTER_SETTER_REF(color_t, color);
		GETTER_SETTER_REF(std::string, texture_path);
		GETTER_SETTER(bool, show_hitbox);
		GETTER_SETTER(bool, render);
		
		public:
			~base_object_t();
			base_object_t() {};
			base_object_t(
				const hitbox_t& hitbox, 
				const point_t& position, 
				const color_t& color
			);
			base_object_t(
				const hitbox_t& hitbox, 
				const point_t& position, 
				const color_t& color, 
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
            virtual bool load_texture (SDL_Renderer *renderer);
	};

    class object_t : public base_object_t
	{
		protected:
			vector_t velocity;
			vector_t resulting_force = vector_t(0.0f, 0.0f);

		GETTER_SETTER_REF(vector_t, velocity);
		GETTER_SETTER_REF(vector_t, resulting_force);
		OO_ENCAPSULATE(float, mass);

		public:
			object_t() {};
			object_t(
				const hitbox_t& hitbox, 
				const point_t& position, 
				const color_t& color,
				float mass
			);
			object_t(
				const hitbox_t& hitbox, 
				const point_t& position, 
				const color_t& color, 
				float mass,
				const char *texture_path
			);

		public:
			inline void add_to_resulting_force (const vector_t& vector)
			{
				this->resulting_force.x += vector.x;
				this->resulting_force.y += vector.y;
			}

		public:
			virtual void handle_object_collision (const object_t& object) {};
            virtual void handle_wside_collision (const window_side_t& wside) {};
            bool load_texture (SDL_Renderer *renderer) override;
	};

	class ui_text_t : public base_object_t
	{
        OO_ENCAPSULATE(std::string, message);
        OO_ENCAPSULATE(unsigned int, font_size);

		public:
			ui_text_t() {};
			ui_text_t(
				const hitbox_t& hitbox, 
				const point_t& position, 
				const color_t& color, 
				const char *texture_path,
				const char *message,
				unsigned int font_size
			);

		public:
            bool load_texture (SDL_Renderer *renderer) override;
	};
}

#endif
