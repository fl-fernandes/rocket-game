#include "object.h"

namespace engine
{
    object_t::object_t(
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color
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
		const hitbox_t& hitbox, 
		const point_t& position, 
		const color_t& color, 
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

	bool object_t::load_texture (SDL_Renderer *renderer)
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
}