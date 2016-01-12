#pragma once

#ifndef Enemy_H
#define Enemy_H

class Enemy
{
protected:
	int state, speed;
public:
	int sprite, health;
	float aimDir, locationX, locationY;
	Enemy(int, float, float, int, int);
	~Enemy();
	virtual void Move(float, float, float); //moves the enemy
	virtual void Attack(); //the enemy attacks
	virtual void GetHit(); //the enemy gets hit
	virtual bool Die(); //the enemy dies
};

#endif
