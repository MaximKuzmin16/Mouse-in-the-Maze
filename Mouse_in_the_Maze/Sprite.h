#pragma once
#include "Game_Object.h"
#include "Drawing.h"

class Sprite : public Game_Object, Drawing
{
	SDL_Surface* surface;
public:
	Sprite(void);
	~Sprite(void);
	void Set_Sprite(string);
	SDL_Surface* Get_Sprite();
	void Draw(SDL_Surface*) override;
	void Draw(SDL_Surface*, int x_offset, int y_offset);
	void Clear_Sprite();
};

