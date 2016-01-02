#include "Player.h"
#include "Weapon.h"
#include <math.h>  

const float halfPi = 1.5707963f;

Player::Player()
{
	locationX = 10;
	locationY = 10;
	movementSpeed = 2;
	aimDir = 0;
}

Player::Player(int InputSpeed, float LocX, float LocY, int imagenum, Weapon inputWeapon)
{
	playerWeapon = inputWeapon;
	locationX = LocX;
	locationY = LocY;
	image = imagenum;
	movementSpeed = InputSpeed;
	aimDir = 0;
}

void Player::Look(float x, float y)
{
	float deltaY = locationY+18 - y;
	float deltaX = locationX+10 - x;
	aimDir = atan2f(deltaY, deltaX) - halfPi;
	playerWeapon.aimDir = aimDir;
}

void Player::Move(float x, float y, float time)
{
	if (x < 0)
	{
		locationX = locationX + floorf(movementSpeed*(x*(time * 100)));
		playerWeapon.locationX = locationX;
	}
	else
	{
		locationX = locationX + ceilf(movementSpeed*(x*(time * 100)));
		playerWeapon.locationX = locationX;
	}

	if (y < 0)
	{
		locationY = locationY + floorf(movementSpeed*(y*(time * 100)));
		playerWeapon.locationY = locationY;
	}
	else
	{
		locationY = locationY + ceilf(movementSpeed*(y*(time * 100)));
		playerWeapon.locationY = locationY;
	}
}


Player::~Player()
{

}
