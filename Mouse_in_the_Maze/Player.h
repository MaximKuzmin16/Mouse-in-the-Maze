#pragma once
#include "Sprite.h"
#include "Moving.h"

class Player : public Sprite, public Moving
{
	int hp;
public:
	Player();
	void Move() override;
	void Add_hp(int hp);
	void Set_hp(int hp);
	int Get_hp() { return hp; };
};

