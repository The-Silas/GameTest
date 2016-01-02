#pragma once

#ifndef MARINE_H
#define MARINE_H

#include "Enemy.h"

class Marine : public Enemy
{
protected:
	int turnRate;
	void Wander(float);
public:
	int legSprite;
	void Move(float);
	void Attack();
	void GetHit();
	void Die();
	Marine(int InputSprite, int LocX, int LocY, int InputHealth,
		int InputSpeed) : Enemy(InputSprite, LocX, LocY, InputHealth, InputSpeed)
	{
		turnRate = 0;
	};
};
#endif