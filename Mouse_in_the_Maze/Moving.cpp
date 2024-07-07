#include "Moving.h"

Moving::Moving(void)
{
	dir.x = 0;
	dir.y = 0;
	speed = 0;
}

void Moving::Set_Direction(int dir_x, int dir_y)
{
	dir.x = dir_x;
	dir.y = dir_y;
}

void Moving::Set_Speed(double speed)
{
	this->speed = speed;
}
