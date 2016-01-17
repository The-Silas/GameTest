#include "Weapon.h"
#include <math.h>  


Weapon::Weapon(int Inputsprite, int Inputspread,
	int InputreloadTime, int InputrateofFire, float LocX,
	float LocY, float InputaimDir, int InputProjectileSpeed,
	bool InputFriendly, int InputProjectileDamage, int InputProjectileSprite,
	float InputOffsetX, float InputOffsetY, float InputProjectileHealth,
	int sound, bool InputFullAuto)
{
	sprite = Inputsprite;
	spread = Inputspread;
	reloadTime = InputreloadTime;
	rateofFire = InputrateofFire;
	locationX = LocX;
	locationY = LocY;
	aimDir = InputaimDir;
	projectileDamage = InputProjectileDamage;
	projectileSpeed = InputProjectileSpeed;
	friendly = InputFriendly;
	projectileSprite = InputProjectileSprite;
	weaponCycle = 0;
	weaponOffsetX = InputOffsetX;
	weaponOffsetY = InputOffsetY;
	projectileHealth = InputProjectileHealth;
	soundID = sound;
	fullAuto = InputFullAuto;
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{

}

bool Weapon::CanFire()
{
	if (weaponCycle <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Projectile Weapon::Fire(float random)
{
	float ProjectileDirection;
	if (random - 50 == 0)
	{
		ProjectileDirection = aimDir;
	}
	else
	{
		ProjectileDirection = aimDir + ((random - 50) / 1000)*spread;
	}
	weaponCycle = rateofFire;

	return Projectile(projectileSprite,friendly, locationX + (sinf(aimDir)*weaponOffsetY) + (cosf(aimDir) * weaponOffsetX),
		locationY - (cosf(aimDir) * weaponOffsetY) + (sinf(aimDir) * weaponOffsetX),
		ProjectileDirection,projectileSpeed, projectileDamage, projectileHealth);
}

void Weapon::cycle(float time)
{
	if (weaponCycle > 0)
	{
		weaponCycle = weaponCycle - (time*20);
	}

}
