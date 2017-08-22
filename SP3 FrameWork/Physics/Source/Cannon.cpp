#include "Cannon.h"


Cannon::Cannon()
{
}

Cannon::~Cannon()
{
}

void Cannon::Init(void)
{
	Weapon_Info::Init();
	projectile_type = Projectile::PROJECTILE_TYPE::CANNON_BALL_PROJECTILE;
	d_timeBetweenShots = 3;
	d_elapsedTime = 0.0;
	b_Fire = true;
	
	//add these to have burst fires

	//d_Burst_timeBetweenShots = 0.5;
	//d_Burst_elapsedTime = 0.0;
	//b_Burst_Fire = true;

	//i_maxbullet = 5;
	i_maxbullet=1;
}