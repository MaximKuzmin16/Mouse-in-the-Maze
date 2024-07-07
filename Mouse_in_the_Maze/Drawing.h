#pragma once
#include <SDL.h>

#include <iostream>
using namespace std;

class Drawing
{
public:
	virtual void Draw(SDL_Surface*) = 0;
	virtual void Draw(SDL_Surface*, int x_offset, int y_offset) = 0;
};

