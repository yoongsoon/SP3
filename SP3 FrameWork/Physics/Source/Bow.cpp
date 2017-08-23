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

	d_Burst_timeBetweenShots = 0.1;
	d_Burst_elapsedTime = 0.0;
	b_Burst_Fire = true;

	i_maxbullet = 5;
}