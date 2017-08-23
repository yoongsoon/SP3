#include "Catapult.h"


Catapult::Catapult()
{
}

Catapult::~Catapult()
{
}

void Catapult::Init(void)
{
	Weapon_Info::Init();
	projectile_type = Projectile::PROJECTILE_TYPE::ROCK_PROJECTILE;
	d_timeBetweenShots = 7;
	d_elapsedTime = 0.0;
	b_Fire = true;

	//add these to have burst fires vv

	//d_Burst_timeBetweenShots = 0.5;
	//d_Burst_elapsedTime = 0.0;
	//b_Burst_Fire = true;
	//i_maxbullet = 5;
	i_maxbullet = 1;
}