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

	d_timeBetweenShots = 1;
	d_elapsedTime = 0.0;
	b_Fire = true;
}