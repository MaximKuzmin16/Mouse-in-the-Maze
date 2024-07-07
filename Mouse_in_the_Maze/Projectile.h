#pragma once
#include "Sprite.h"
#include "Moving.h"

class Projectile : public Sprite, public Moving
{
public:
	Projectile();
	void Move() override;
};

