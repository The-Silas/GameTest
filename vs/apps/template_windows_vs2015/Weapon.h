#pragma once

#ifndef Weapon_H
#define Weapon_H
#include "Projectile.h"

class Weapon
{
public:
	int sprite, spread, reloadTime, rateofFire;
	float locationX, locationY, aimDir;
	Weapon(int,int,int,int, float, float, float, int, bool,
		int, int, float, float, float);
	Weapon();
	~Weapon();
	bool CanFire();
	Projectile Fire(float);
	void cycle(float);
protected:
	float weaponCycle, weaponOffsetX, weaponOffsetY, projectileHealth;
	int projectileDamage, projectileSpeed, projectileSprite;
	bool friendly;
};

#endif
