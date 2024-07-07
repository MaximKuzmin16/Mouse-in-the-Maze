#include "Game_Object.h"

Game_Object::Game_Object(void)
{
	transform.x = 0;
	transform.y = 0;
	transform.w = 0;
	transform.h = 0;
}

void Game_Object::Set_Object_Name(string name)
{
	obj_name = name;
}

void Game_Object::Set_Position(int x, int y)
{
	transform.x = x;
	transform.y = y;
}

void Game_Object::Set_Size(int w, int h)
{
	transform.w = w;
	transform.h = h;
}

void Game_Object::Set_Transform(int x, int y, int w, int h)
{
	transform.x = x;
	transform.y = y;
	transform.w = w;
	transform.h = h;
}

SDL_Rect Game_Object::Get_Rect()
{
	return transform;
}
