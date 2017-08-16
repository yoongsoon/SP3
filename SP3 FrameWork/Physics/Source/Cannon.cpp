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

	d_timeBetweenShots = 3;
	d_elapsedTime = 0.0;
	b_Fire = true;
}