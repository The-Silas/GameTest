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

void Marine::Move(float time)
{
	if (state == 0)
	{
		Wander(time);
	}
	locationX = locationX + sinf(aimDir)*time*10*speed;
	locationY = locationY - cosf(aimDir)*time*10*speed;
}

void Marine::Attack()
{

}

void Marine::GetHit()
{

}

void Marine::Die()
{

}

