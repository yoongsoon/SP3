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
}