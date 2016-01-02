#pragma once

#ifndef Projectile_H
#define Projectile_H

class Projectile
{
protected:
	int speed;
	float health;
public:
	int sprite, damage;
	bool friendly, dead;
	float locationXCurrent, locationYCurrent,
		locationXLast, locationYLast, aimDir;
	Projectile(int, bool, float, float, float, int, int, float);
	void Move(float);
	~Projectile();
};

#endif

