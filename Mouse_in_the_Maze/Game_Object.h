#pragma once
#include <SDL.h>

#include <iostream>
using namespace std;

class Game_Object
{
protected:
	SDL_Rect transform;
	string obj_name;
public:
	Game_Object(void);
	void Set_Object_Name(string name);
	string Get_Object_Name() { return obj_name; };
	void Set_Position(int, int);
	void Set_Size(int, int);
	void Set_Transform(int, int, int, int);
	SDL_Rect Get_Rect();
};

