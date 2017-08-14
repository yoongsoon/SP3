#include "WeaponInfo.h"



Weapon_Info::Weapon_Info()
	:d_timeBetweenShots(0.5)
	, d_elapsedTime(0.0)
	, f_Fire_Rate(1)
	, b_Fire(true)
	, d_Burst_timeBetweenShots(0.2)
	, d_Burst_elapsedTime(0.0)
	, f_Burst_Fire_Rate(2)
	, b_Burst_Fire(false)
{

}
Weapon_Info::~Weapon_Info()
{

}

void Weapon_Info::Init(void)
{

}
void Weapon_Info::Update(const double dt)
{

}


void Weapon_Info::Set_d_timeBetweenShots(double d_timeBetweenShots)
{
	this->d_timeBetweenShots = d_timeBetweenShots;
}
void Weapon_Info::Set_d_elapsedTime(double d_elapsedTime)
{
	this->d_elapsedTime = d_elapsedTime;
}
void Weapon_Info::Set_f_Fire_Rate(float f_Fire_Rate)
{
	this->f_Fire_Rate = f_Fire_Rate;
}
void Weapon_Info::Set_b_Fire(bool b_Fire)
{
	this->b_Fire = b_Fire;
}

void Weapon_Info::Set_d_Burst_timeBetweenShots(double d_Burst_timeBetweenShots)
{
	this->d_Burst_timeBetweenShots = d_Burst_timeBetweenShots;
}
void Weapon_Info::Set_d_Burst_elapsedTime(double d_Burst_elapsedTime)
{
	this->d_Burst_elapsedTime = d_Burst_elapsedTime;
}
void Weapon_Info::Set_f_Burst_Fire_Rate(float d_Burst_elapsedTime)
{
	this->f_Burst_Fire_Rate = d_Burst_elapsedTime;
}
void Weapon_Info::Set_b_Burst_Fire(bool b_Burst_Fire)
{
	this->b_Burst_Fire = b_Burst_Fire;
}

double Weapon_Info::Get_d_timeBetweenShots()
{
	return d_timeBetweenShots;
}
double Weapon_Info::Get_d_elapsedTime()
{
	return d_elapsedTime;
}
float Weapon_Info::Get_f_Fire_Rate()
{
	return f_Fire_Rate;
}
bool Weapon_Info::Get_b_Fire()
{
	return b_Fire;
}

double Weapon_Info::Get_d_Burst_timeBetweenShots()
{
	return d_Burst_timeBetweenShots;
}
double Weapon_Info::Get_d_Burst_elapsedTime()
{
	return d_Burst_elapsedTime;
}
float Weapon_Info::Get_f_Burst_Fire_Rate()
{
	return f_Burst_Fire_Rate;
}
bool Weapon_Info::Get_b_Burst_Fire()
{
	return b_Burst_Fire;
}

void Weapon_Info::PrintSelf(void)
{
}
	
//	//time in between shots
//	double d_timeBetweenShots;
//	//elapsed time in between shots
//	double d_elapsedTime;//starts Null
//						 //fire rate of triggered
//	float f_Fire_Rate;
//	//Flag availability to Fire
//	bool b_Fire;
//	//_________________BURST_____FIRE_______________________________
//
//	//elapsed time in between projectiles
//	double d_Burst_timeBetweenShots;
//	//elapsed time of burst
//	double d_Burst_elapsedTime;
//	//fire rate of projectiles in between projectiles
//	float f_Burst_Fire_Rate;
//	//Flag if burst firing is done/available
//	bool b_Burst_Fire;
//	//std::list</*Projectile*/>bullets;
//
//	//bool b_Fired
//};
