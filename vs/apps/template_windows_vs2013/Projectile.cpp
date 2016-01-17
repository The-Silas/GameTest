#include "Projectile.h"
#include <math.h>  


Projectile::Projectile(int InputSprite, bool Inputfriendly, float LocX,
	float LocY, float InputaimDir, int Inputspeed, int Inputdamage, float InputHealth)
{
	friendly = Inputfriendly;
	locationXCurrent = LocX;
	locationYCurrent = LocY;
	aimDir = InputaimDir;
	sprite = InputSprite;
	speed = Inputspeed;
	damage = Inputdamage;
	health = InputHealth;
	dead = false;
	locationXLast = locationXCurrent;
	locationYLast = locationYCurrent;
}

void Projectile::Move(float time)
{
	locationXLast = locationXCurrent;
	locationYLast = locationYCurrent;
	locationXCurrent = locationXCurrent + speed*sinf(aimDir)*time;
	locationYCurrent = locationYCurrent - speed*cosf(aimDir)*time;
	health = health - time*speed;
	if (health <= 0)
	{
		dead = true;
	}
}


Projectile::~Projectile()
{

}
