#pragma once
#include "Game_Object.h"
#include "Projectile.h"
#include <vector>
using namespace std;

class Projectile_Spawner : public Game_Object
{
	int damage_kol;
	int all_kol;
	int this_kol;
	int time;
	int last_time;

	int dir;

public:
	Projectile_Spawner();
	void Set_Dir(int x) { dir = x; };
	void Update(vector<Projectile*>* vect, string name);
	void Set_spawner(int x, int y) { damage_kol = x; all_kol = y; };
};

