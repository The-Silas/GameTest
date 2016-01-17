// Includes
#include "template.h"
#include "Settings.h"
#include "Enemy.h"
#include "Marine.h"
#include "Player.h"
#include "Projectile.h"
#include <ctime>

// Namespace
using namespace AGK;

app App;

std::vector<Marine> marines; // empty
std::vector<Projectile> bullets;
Player player;
float thisFrame, lastFrame, difference;
const int friendliesGroup = 0;
const int enemiesGroup = 1;
const int bulletsGroup = 2;

void app::Begin(void)
{
	std::srand(std::time(0)); // use current time as seed for random generator
	Settings gameSettings;
	gameSettings.Load();

	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);
	agk::SetGlobal3DDepth(10000);

	//load background
	int street = agk::LoadImage("intersection.png");
	street = agk::CreateSprite(street);
	agk::SetSpritePosition(street, 0, 0);
	agk::SetSpriteDepth(street, 10000);

	//load player
	int Pimage = agk::LoadImage("player.png");
	int pistolsprite = agk::CreateSprite(agk::LoadImage("pistol_0.png"));
	agk::AddSpriteAnimationFrame(pistolsprite, agk::LoadImage("pistol_1.png"));
	agk::AddSpriteAnimationFrame(pistolsprite, agk::LoadImage("pistol_0.png"));
	agk::AddSpriteAnimationFrame(pistolsprite, agk::LoadImage("pistol_g.png"));
	agk::SetSpriteOffset(pistolsprite, 20, 36);

	int gunshotSound = agk::LoadSound("gunshot-1.wav");
	Weapon w = Weapon(pistolsprite, 2, 10, 5, 500, 400, 0, 2000, true, 25,
		agk::LoadImage("pistol_bullet.png"), 7, 36, 500, gunshotSound, true);
	player = Player(1, 500, 400, agk::CreateSprite(Pimage), w);
	agk::SetSpriteOffset(player.image, 20, 36);
	agk::SetSpriteGroup(player.image, friendliesGroup);
	agk::SetSpritePositionByOffset(player.image,
		player.locationX, player.locationY);
	agk::SetSpriteShapeCircle(player.image, 20, 36, 14);
	agk::SetSpriteAngleRad(player.image, player.aimDir);
	agk::SetSpriteDepth(player.image, friendliesGroup);

	//Load enemies
	int Eimage = agk::LoadImage("soldier.png");
	for (int x = 0; x < 1; x++)
	{
		int mpistolsprite = agk::CreateSprite(agk::LoadImage("pistol_0.png"));
		agk::AddSpriteAnimationFrame(mpistolsprite, agk::LoadImage("pistol_1.png"));
		agk::AddSpriteAnimationFrame(mpistolsprite, agk::LoadImage("pistol_0.png"));
		agk::AddSpriteAnimationFrame(mpistolsprite, agk::LoadImage("pistol_g.png"));
		agk::SetSpriteOffset(mpistolsprite, 20, 36);

		marines.push_back(Marine(agk::CreateSprite(Eimage), x * 60, 200, 100, 10,
			Weapon(mpistolsprite, 2, 10, 5, 500, 400, 0, 2000, false, 25,
			agk::LoadImage("pistol_bullet.png"), 7, 36, 500, gunshotSound, true)));

		agk::SetSpritePosition(marines[x].sprite,
			marines[x].locationX, marines[x].locationY);
		agk::SetSpriteAngle(marines[x].sprite, marines[x].aimDir);
		agk::SetSpriteOffset(marines[x].sprite, 20, 36);
		agk::SetSpriteShapeCircle(marines[x].sprite, 0, 0, 14);
		agk::SetSpriteGroup(marines[x].sprite, enemiesGroup);
		agk::SetSpriteDepth(marines[x].sprite, enemiesGroup);
	}

	

	

	//Load muzzleflash

	lastFrame = agk::Timer();
	agk::SetVSync(1);
	agk::SetJoystickScreenPosition(50, 300, 64);
}

void app::Loop(void)
{
	thisFrame = agk::Timer();
	difference = thisFrame - lastFrame;
	lastFrame = thisFrame;

	//Check to see pointer held
	if (agk::GetPointerState() == 1)
	{
		if (player.playerWeapon.CanFire() && player.playerWeapon.fullAuto)
		{
			Projectile p = player.playerWeapon.Fire(std::rand() % 100);
			p.sprite = agk::CreateSprite(p.sprite);
			agk::SetSpriteShape(p.sprite, 1);
			agk::SetSpriteDepth(p.sprite, bulletsGroup);
			agk::SetSpritePhysicsIsBullet(p.sprite, 1);
			agk::SetSpritePhysicsIsBullet(p.sprite, 1);
			agk::SetSpriteAngleRad(p.sprite, p.aimDir);
			agk::SetSpriteGroup(p.sprite, bulletsGroup);
			bullets.push_back(p);
			agk::PlaySprite(player.playerWeapon.sprite, 10, 0, 1, 2);
			agk::PlaySound(player.playerWeapon.soundID);
			agk::CreatePointLight(1, p.locationXCurrent, p.locationYCurrent,
				50, 1000, 0, 255, 0);
		}
	}

	//Check to see pointer click
	if (agk::GetPointerPressed() == 1)
	{
		if (player.playerWeapon.CanFire() && !player.playerWeapon.fullAuto)
		{
			Projectile p = player.playerWeapon.Fire(std::rand() % 100);
			p.sprite = agk::CreateSprite(p.sprite);
			agk::SetSpriteShape(p.sprite, 1);
			agk::SetSpriteDepth(p.sprite, bulletsGroup);
			agk::SetSpritePhysicsIsBullet(p.sprite, 1);
			agk::SetSpritePhysicsIsBullet(p.sprite, 1);
			agk::SetSpriteAngleRad(p.sprite, p.aimDir);
			agk::SetSpriteGroup(p.sprite, bulletsGroup);
			bullets.push_back(p);
			agk::PlaySprite(player.playerWeapon.sprite, 10, 0, 1, 2);
			agk::PlaySound(player.playerWeapon.soundID);
		}
	}


	//Update bullets
	for (int w = 0; w < bullets.size(); w++)
	{
		if (bullets[w].dead)
		{
			agk::DeleteSprite(bullets[w].sprite);
			bullets[w].~Projectile();
			bullets.erase(bullets.begin() + w);
		}
		else
		{
			bullets[w].Move(difference);

			agk::SetSpritePosition(bullets[w].sprite, bullets[w].locationXCurrent, bullets[w].locationYCurrent);
		}
	}

	//Update player
	player.Look(agk::GetPointerX(), agk::GetPointerY());
	player.Move(agk::GetJoystickX(), agk::GetJoystickY(), difference);
	agk::Print(agk::GetJoystickX());
	agk::Print(agk::GetJoystickY());
	player.playerWeapon.cycle(difference);
	agk::SetSpritePositionByOffset(player.playerWeapon.sprite,
		player.playerWeapon.locationX, player.playerWeapon.locationY);
	agk::SetSpriteAngleRad(player.playerWeapon.sprite, player.playerWeapon.aimDir);
	agk::SetSpritePositionByOffset(player.image,
		player.locationX, player.locationY);
	agk::SetSpriteAngleRad(player.image, player.aimDir);
	agk::SetSpriteColor(player.image, 255, 255, 255, 255);

	//Update enemies
	for (int w = 0; w < marines.size(); w++)
	{
		if (marines[w].health <= 0)
		{
			if (marines[w].Die())
			{
				agk::DeleteSprite(marines[w].sprite);
				marines.erase(marines.begin() + w);
			}
		}
		else
		{
			marines[w].Move(difference, player.locationX, player.locationY);
			agk::SetSpritePosition(marines[w].sprite,
				marines[w].locationX, marines[w].locationY);
			agk::SetSpriteAngleRad(marines[w].sprite, marines[w].aimDir);
			agk::SetSpriteColor(marines[w].sprite, 255, 255, 255, 255);
			marines[w].weapon.cycle(difference);
			if (marines[w].CanHitPlayer() && marines[w].weapon.CanFire())
			{
				Projectile p = marines[w].weapon.Fire(std::rand() % 100);
				p.sprite = agk::CreateSprite(p.sprite);
				agk::SetSpriteShape(p.sprite, 1);
				agk::SetSpriteDepth(p.sprite, bulletsGroup);
				agk::SetSpritePhysicsIsBullet(p.sprite, 1);
				agk::SetSpritePhysicsIsBullet(p.sprite, 1);
				agk::SetSpriteAngleRad(p.sprite, p.aimDir);
				agk::SetSpriteGroup(p.sprite, bulletsGroup);
				bullets.push_back(p);
				agk::PlaySprite(player.playerWeapon.sprite, 10, 0, 1, 2);
				agk::PlaySound(player.playerWeapon.soundID);
			}

			if (marines[w].health < 100)
			{
				int color = agk::MakeColor(0, 255, 0);
				agk::DrawBox(marines[w].locationX, marines[w].locationY,
					marines[w].locationX + (marines[w].health / 2), marines[w].locationY + 3,
					color, color, color, color, 1);

			}
		}
	}

	//Check collisions
	for (int w = 0; w < bullets.size(); w++)
	{
		if (bullets[w].friendly)
		{
			for (int v = 0; v < marines.size(); v++)
			{

				if (agk::SpriteRayCastSingle(marines[v].sprite,
					bullets[w].locationXLast, bullets[w].locationYLast,
					bullets[w].locationXCurrent, bullets[w].locationYCurrent) == 1)
				{
					agk::DrawLine(bullets[w].locationXLast, bullets[w].locationYLast,
					bullets[w].locationXCurrent, bullets[w].locationYCurrent, 255, 0, 0);
					agk::SetSpriteColor(agk::GetRayCastSpriteID(), 255, 0, 0, 255);
					bullets[w].dead = true;
					marines[v].health = marines[v].health - bullets[w].damage;
				}
			}

		}
		else
		{
			if (agk::GetSpriteCollision(
				player.image, bullets[w].sprite))
			{
				agk::DrawLine(bullets[w].locationXLast, bullets[w].locationYLast,
					bullets[w].locationXCurrent, bullets[w].locationYCurrent, 255, 0, 0);
				agk::SetSpriteColor(player.image, 255, 0, 0, 255);
				bullets[w].dead = true;
			}
		}
	}

	agk::Print(agk::ScreenFPS());
	agk::Print(difference);
	agk::Sync();
}


void app::End (void)
{
	for (int x = 0; x < marines.size(); x++)
	{
		agk::DeleteSprite(marines[x].sprite);
	}
	for (int x = 0; x < bullets.size(); x++)
	{
		agk::DeleteSprite(bullets[x].sprite);
	}
}

