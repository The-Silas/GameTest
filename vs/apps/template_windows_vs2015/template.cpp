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

void app::Begin(void)
{
	std::srand(std::time(0)); // use current time as seed for random generator
	Settings gameSettings;
	gameSettings.Load();

	agk::SetVirtualResolution (1024, 768);
	agk::SetClearColor( 151,170,204 ); // light blue
	agk::SetSyncRate(60,0);
	agk::SetScissor(0,0,0,0);

	//load background
	int street = agk::LoadImage("street.png");
	agk::SetSpritePosition(agk::CreateSprite(street),
		0, 0);

	//Load enemies
	int Eimage = agk::LoadImage("soldier.png");
	for (int x = 0; x < 10; x++)
	{
		
		marines.push_back(Marine(agk::CreateSprite(Eimage), x * 60, 200, 100,10));
		
		agk::SetSpritePosition(marines[x].sprite,
			marines[x].locationX, marines[x].locationY);
		agk::SetSpriteAngle(marines[x].sprite, marines[x].aimDir);
		agk::SetSpriteOffset(marines[x].sprite, 20, 36);
	}

	//load player
	int Pimage = agk::LoadImage("player.png");
	int pistolsprite = agk::CreateSprite( agk::LoadImage("pistol_0.png"));
	agk::AddSpriteAnimationFrame(pistolsprite, agk::LoadImage("pistol_1.png"));
	agk::AddSpriteAnimationFrame(pistolsprite, agk::LoadImage("pistol_0.png"));
	agk::SetSpriteOffset(pistolsprite, 20, 36);
	

	Weapon w = Weapon(pistolsprite,2,10,5,500,400,0,2000,true,25,
		agk::LoadImage("pistol_bullet.png"));
	player = Player(1, 500, 400, agk::CreateSprite(Pimage),w);
	agk::SetSpriteOffset(player.image, 20, 36);
	agk::SetSpritePositionByOffset(player.image,
		player.locationX, player.locationY);
	agk::SetSpriteAngleRad(player.image, player.aimDir);

	lastFrame = agk::Timer();
	agk::SetVSync(1);
	agk::SetJoystickScreenPosition(50, 300, 64);
}

void app::Loop (void)
{
	thisFrame = agk::Timer();
	difference = thisFrame - lastFrame;
	lastFrame = thisFrame;

	player.playerWeapon.cycle(difference);
	//Check to see click
	if (agk::GetPointerPressed() == 1)
	{
		if (player.playerWeapon.CanFire())
		{
			Projectile p = player.playerWeapon.Fire(std::rand()%100);
			p.sprite = agk::CreateSprite(p.sprite);
			agk::SetSpritePhysicsIsBullet(p.sprite, 1);
			agk::SetSpriteAngleRad(p.sprite, p.aimDir);
			bullets.push_back(p);
			agk::PlaySprite(player.playerWeapon.sprite, 10, 0,1,2);
		}
	}

	for (int w = 0; w < bullets.size(); w++)
	{
		//bullets[w].Move(difference);

		agk::SetSpritePosition(bullets[w].sprite, bullets[w].locationX, bullets[w].locationY);
	}

	player.Look(agk::GetPointerX(), agk::GetPointerY());
	player.Move(agk::GetJoystickX(), agk::GetJoystickY(), difference);
	agk::Print(agk::GetJoystickX());
	agk::Print(agk::GetJoystickY());

	for (int w = 0; w < marines.size(); w++)
	{
		marines[w].Move(difference);
		agk::SetSpritePosition(marines[w].sprite,
			marines[w].locationX, marines[w].locationY);
		agk::SetSpriteAngleRad(marines[w].sprite, marines[w].aimDir);
	}

	agk::SetSpritePositionByOffset(player.playerWeapon.sprite,
		player.playerWeapon.locationX, player.playerWeapon.locationY);
	agk::SetSpriteAngleRad(player.playerWeapon.sprite, player.playerWeapon.aimDir);
	agk::SetSpritePositionByOffset(player.image,
		player.locationX, player.locationY);
	agk::SetSpriteAngleRad(player.image, player.aimDir);
	agk::Print( agk::ScreenFPS() ); 
	agk::Print(difference);
	agk::Sync();
}


void app::End (void)
{
	for (int x = 0; x < 10; x++)
	{
		agk::DeleteSprite(marines[x].sprite);
	}
}
