#pragma once
#include "Weapon.h"

class Player
{
protected:
	int movementSpeed;
public:
	int image;
	Weapon playerWeapon;
//Weapon
	float locationX, locationY, aimDir;
	Player(int, float, float, int, Weapon);
	void Look(float, float);
	void Move(float, float, float);
	Player();
	~Player();
};

