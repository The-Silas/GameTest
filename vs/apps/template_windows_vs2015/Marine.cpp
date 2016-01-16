#include "Marine.h"
#include <math.h>  

const double pi = 3.1415926535897;

void Marine::Wander(float time)
{
	aimDir = aimDir + 2*time;
	if (aimDir >= 2 * pi)
	{
		aimDir = aimDir - (2 * pi);
	}
}

void Marine::AimAtPlayer(float time)
{
	float deltaY = playerY - locationY;
	float deltaX = playerX - locationX;

	float angle = atan2f(deltaY, deltaX);

	if (angle < aimDir - (pi / 2))
	{
		aimDir = aimDir - (2 * time);
	}
	else if (angle > aimDir - (pi / 2))
	{
		aimDir = aimDir + (2 * time);
	}
}

void Marine::Move(float time, float PlayerX, float PlayerY)
{
	playerX = PlayerX;
	playerY = PlayerY;

	if (state == 0)
	{
		AimAtPlayer(time);
	}
	locationX = locationX + sinf(aimDir)*time*10*speed;
	locationY = locationY - cosf(aimDir)*time*10*speed;


	weapon.aimDir = aimDir;
	weapon.locationX = locationX;
	weapon.locationY = locationY;
}

void Marine::Attack()
{

}

void Marine::GetHit()
{

}

bool Marine::Die()
{
	return true;
}

bool Marine::CanHitPlayer()
{
	float deltaY = playerY - locationY;
	float deltaX = playerX - locationX;

	float angle = atan2f(deltaY, deltaX);
	
	if (fabsf(angle - (aimDir - (pi / 2))) < .2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

