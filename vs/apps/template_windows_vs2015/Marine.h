#pragma once

#ifndef MARINE_H
#define MARINE_H

#include "Enemy.h"
#include "Weapon.h"

class Marine : public Enemy
{
protected:
	float playerX, playerY;
	int turnRate;
	void Wander(float);
	void AimAtPlayer(float);
public:
	Weapon weapon;
	void Move(float, float, float);
	void Attack();
	void GetHit();
	bool Die();
	bool CanHitPlayer();
	Marine(int InputSprite, int LocX, int LocY, int InputHealth,
		int InputSpeed, Weapon InputWeapon) : Enemy(InputSprite, LocX, LocY, InputHealth, InputSpeed)
	{
		weapon = InputWeapon;
		
		turnRate = .3;
	};
};
#endif