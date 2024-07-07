#include <SDL.h>
#include <SDL_ttf.h>

#include "Game.h"

#include <iostream>
using namespace std;

#undef main

bool Init_SDL();
void Close_SDL();

int main()
{
	if (!Init_SDL())
	{
		return 1;
	}

	Game* game;
	game = new Game;
	while(game->Is_Running())
	{
		game->Update();
		SDL_Delay(10/*1000 / 60.0*/);
	}
	delete game;

	Close_SDL();
	return 0;
}

bool Init_SDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		cout << SDL_GetError() << endl;
		return false;
	}

	if (TTF_Init())
	{
		SDL_Quit();
		cout << TTF_GetError() << endl;
		return false;
	}

	return true;
}

void Close_SDL()
{
	SDL_Quit();
	TTF_Quit();
}