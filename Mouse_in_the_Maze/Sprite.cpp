#include "Sprite.h"

Sprite::Sprite(void)
{
	surface = nullptr;
}

Sprite::~Sprite(void)
{
	Clear_Sprite();
}

void Sprite::Set_Sprite(string name)
{
	if(surface)
	{
		SDL_FreeSurface(surface);
	}

	surface = SDL_LoadBMP(name.c_str());


	SDL_SetColorKey(surface, true, 0xFF00FF);
}

SDL_Surface* Sprite::Get_Sprite()
{
	return surface;
}

void Sprite::Draw(SDL_Surface* main_surface)
{
	if(surface)
	{
		SDL_BlitSurface(surface, NULL, main_surface, &transform);
	}
}

void Sprite::Draw(SDL_Surface* main_surface, int x_offset, int y_offset)
{
	if (surface)
	{
		SDL_Rect offset_rect = transform;
		offset_rect.x += x_offset;
		offset_rect.y += y_offset;

		SDL_BlitSurface(surface, NULL, main_surface, &offset_rect);
	}
}

void Sprite::Clear_Sprite()
{
	if(surface)
	{
		SDL_FreeSurface(surface);
		surface = nullptr;
	}
}