#include "Bow.h"


Bow::Bow()
{
}

Bow::~Bow()
{
}

void Bow::Init(void)
{
	Weapon_Info::Init();
	projectile_type = Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE;
	d_timeBetweenShots = 1;
	d_elapsedTime = 0.0;
	b_Fire = true;
}