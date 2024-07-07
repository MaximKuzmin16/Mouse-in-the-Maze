#include "Player.h"

Player::Player()
{
	hp = 100;
	speed = 5;
	Set_Sprite("sprites\\mouse.bmp");
	Set_Size(64, 64);
}

void Player::Move()
{
	transform.x += dir.x * speed;
	transform.y += dir.y * speed;
}

void Player::Add_hp(int hp)
{
	this->hp += hp;
}

void Player::Set_hp(int hp)
{
	this->hp = hp;
}
