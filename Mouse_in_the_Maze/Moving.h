#pragma once
#include <SDL.h>

class Moving
{
protected:
	SDL_Point dir;
	double speed;
public:
	Moving(void);
	void Set_Direction(int dir_x, int dir_y);
	void Set_Speed(double speed);

	SDL_Point Get_Direction() { return dir; };
	double Get_Speed() { return speed; };

	virtual void Move() = 0;
};

