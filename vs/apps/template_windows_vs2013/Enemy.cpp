
#include "Enemy.h"

Enemy::Enemy(int InputSprite, float LocX, float LocY, int InputHealth, int InputSpeed)
{
	locationX = LocX;
	locationY = LocY;
	sprite = InputSprite;
	aimDir = 0;
	state = 0;
	health = InputHealth;
	speed = InputSpeed;
}

Enemy::~Enemy()
{
}


void Enemy::Move(float time, float PlayerX, float PlayerY)
{
}

void Enemy::Attack()
{
}

void Enemy::GetHit()
{
}

bool Enemy::Die()
{
	return true;
}


