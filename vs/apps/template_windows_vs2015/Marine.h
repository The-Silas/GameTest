#pragma once

#ifndef MARINE_H
#define MARINE_H

#include "Enemy.h"

class Marine : public Enemy
{
protected:
	int turnRate;
	void Wander(float);
	void AimAtPlayer(float, float, float);
public:
	int legSprite;
	void Move(float, float, float);
	void Attack();
	void GetHit();
	bool Die();
	Marine(int InputSprite, int LocX, int LocY, int InputHealth,
		int InputSpeed) : Enemy(InputSprite, LocX, LocY, InputHealth, InputSpeed)
	{
		turnRate = .3;
	};
};
#endif