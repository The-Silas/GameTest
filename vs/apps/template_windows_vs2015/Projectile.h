#pragma once

#ifndef Projectile_H
#define Projectile_H

class Projectile
{
protected:
	int speed;
public:
	int sprite, damage;
	bool friendly;
	float locationX, locationY, aimDir;
	Projectile(int, bool, float, float, float, int, int);
	void Move(float);
	~Projectile();
};

#endif

