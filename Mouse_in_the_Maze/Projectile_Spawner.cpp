#include "Projectile_Spawner.h"

Projectile_Spawner::Projectile_Spawner()
{
	damage_kol = 0;
	all_kol = 0;
	this_kol = 0;
	time = 13;
	last_time = 0;
	dir = 0;
}

void Projectile_Spawner::Update(vector<Projectile*>* vect, string name)
{
	last_time++;
	if(last_time == time)
	{
		last_time = 0;
		if(this_kol < damage_kol)
		{
			Projectile* temp = new Projectile;
			switch(dir)
			{
			case 0:
				temp->Set_Sprite(name + "_right.bmp");
				temp->Set_Direction(1, 0);
				temp->Set_Position(transform.x + 128, transform.y + 32);
				break;
			case 1:
				temp->Set_Sprite(name + "_left.bmp");
				temp->Set_Direction(-1, 0);
				temp->Set_Position(transform.x - 64, transform.y + 32);
				break;
			case 2:
				temp->Set_Sprite(name + "_down.bmp");
				temp->Set_Direction(0, 1);
				temp->Set_Position(transform.x + 32, transform.y + 128);
				break;
			case 3:
				temp->Set_Sprite(name + "_up.bmp");
				temp->Set_Direction(0, -1);
				temp->Set_Position(transform.x + 32, transform.y - 64);
				break;
			}
			(*vect).push_back(temp);
		}
		this_kol++;
		if(this_kol == all_kol)
		{
			this_kol = 0;
		}
	}
}
