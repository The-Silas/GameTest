#include "Projectile.h"
#include <math.h>  


Projectile::Projectile(int InputSprite, bool Inputfriendly, float LocX,
	float LocY, float InputaimDir, int Inputspeed, int Inputdamage)
{
	friendly = Inputfriendly;
	locationX = LocX;
	locationY = LocY;
	aimDir = InputaimDir;
	sprite = InputSprite;
	speed = Inputspeed;
	damage = Inputdamage;
}

void Projectile::Move(float time)
{
	locationX = locationX + speed*sinf(aimDir)*time;
	locationY = locationY - speed*cosf(aimDir)*time;
}


Projectile::~Projectile()
{

}
