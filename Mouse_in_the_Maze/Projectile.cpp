#include "Projectile.h"

Projectile::Projectile()
{
	speed = 5;
	Set_Size(64, 64);
}

void Projectile::Move()
{
	transform.x += dir.x * speed;
	transform.y += dir.y * speed;
}
