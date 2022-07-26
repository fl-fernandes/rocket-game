#include "object.h"

namespace engine
{
	coord_t vector_t::prod_int (const vector_t& v1, const vector_t& v2)
	{
		coord_t p;
		p = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		return p;
	}

	coord_t vector_t::get_module ()
	{
		coord_t m;
		m = sqrt(vector_t::prod_int(*this, *this));	
		return m;
	}
	
	void vector_t::set_module (coord_t mod)
	{
		this->divide(this->get_module());
		this->multiply(mod);
	}

    base_object_t::base_object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color
	)
	{
		this->position = position;
		this->hitbox = hitbox;
		this->color = color;
		if (texture_path != "")
			this->set_texture_path(texture_path);
	}

	base_object_t::base_object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color,
		const char *texture_path
	) : base_object_t(hitbox, position, color)
	{
		this->texture_path = texture_path;
	}

	base_object_t::~base_object_t ()
	{
		if (this->texture != nullptr)
			SDL_DestroyTexture(this->texture);
	}

	int base_object_t::load_texture(SDL_Renderer *renderer)
	{
		return 1;
	}

	object_t::object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color,
		float mass
	) : base_object_t(hitbox, position, color)
	{
		this->velocity = vector_t(0, 0);
		this->mass = mass;
	}

	object_t::object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color, 
		float mass,
		const char *texture_path
	) : base_object_t(hitbox, position, color, texture_path)
	{
		this->velocity = vector_t(0, 0);
		this->mass = mass;
	}

	int object_t::load_texture (SDL_Renderer *renderer)
	{
		if (this->texture_path != "" && renderer != nullptr) {
			SDL_Surface *surface = SDL_LoadBMP(this->texture_path.c_str());
			if (surface == nullptr)
				return 1;

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            if (texture == nullptr)
				return 2;
			
			if (this->texture != nullptr)
				SDL_DestroyTexture(this->texture);
			SDL_FreeSurface(surface);
			this->texture = texture;
			return 0;
		}

		return 3;
	}

	ui_text_t::ui_text_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color, 
		const char *texture_path,
		const char *message,
		unsigned int font_size
	) : base_object_t(hitbox, position, color, texture_path)
	{
		this->message = message;
		this->font_size = font_size;
		
		this->font = nullptr;
	}

	int ui_text_t::load_texture (SDL_Renderer *renderer)
	{
		 if (this->texture_path != "" && renderer != nullptr) {
			if (TTF_Init() < 0)	{
				DPRINT("Couldn't initialize SDL TTF");
			}
			
			if (this->font == nullptr) {
				this->font = TTF_OpenFont(this->texture_path.c_str(), this->font_size);
				
				if (!this->font) {
				    C_ASSERT(0);
				}
			}
			
            SDL_Color color = {this->color.r, this->color.g, this->color.b};
            
            SDL_Surface *surface = TTF_RenderText_Solid(this->font, this->message.c_str(), color);

            if (surface == nullptr)
                return 2;

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

            if (texture == nullptr)
                return 3;

            if (this->texture != nullptr)
                SDL_DestroyTexture(this->texture);
            SDL_FreeSurface(surface);
            this->texture = texture;
			
            return 0;
        }

		return 4;
	}
	
	int ui_text_t::set_message (const char *message, SDL_Renderer *renderer)
	{	
		this->message = message;
		
		return this->load_texture(renderer);
	}
}
