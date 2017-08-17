#include "WeaponInfo.h"
#include "Projectile.h"
#include "GameObject.h"

Weapon_Info::Weapon_Info()
	:d_timeBetweenShots(0.5)
	, d_elapsedTime(0.0)
	, i_Fire_Rate(1)
	, b_Fire(true)
	, d_Burst_timeBetweenShots(0.2)
	, d_Burst_elapsedTime(0.0)
	, i_Burst_Fire_Rate(2)
	, b_Burst_Fire(false)
{

}
Weapon_Info::~Weapon_Info()
{

}

void Weapon_Info::Init(void)
{
	d_timeBetweenShots = 3;
	d_elapsedTime = 0.0;
	i_Fire_Rate = 1;
	b_Fire = true;

	d_Burst_timeBetweenShots = 0.2;
	d_Burst_elapsedTime = 0.0;
	i_Burst_Fire_Rate = 2;
	b_Burst_Fire = true;
}
void Weapon_Info::Update(const double dt)
{
	d_elapsedTime += dt;

	if (d_elapsedTime > d_timeBetweenShots)
	{
		b_Fire = true;
		d_elapsedTime = 0.0;
	}
}


void Weapon_Info::Set_d_timeBetweenShots(double d_timeBetweenShots)
{
	this->d_timeBetweenShots = d_timeBetweenShots;
}
void Weapon_Info::Set_d_elapsedTime(double d_elapsedTime)
{
	this->d_elapsedTime = d_elapsedTime;
}
void Weapon_Info::Set_Fire_Rate(int d_Fire_Rate)
{
	d_timeBetweenShots = 60.0 / (double)d_Fire_Rate;
	//this->f_Fire_Rate = f_Fire_Rate;
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
void Weapon_Info::Set_Burst_Fire_Rate(int d_Burst_Fire_Rate)
{
	d_Burst_timeBetweenShots = 60.0 / (double)d_Burst_Fire_Rate;
	//this->f_Burst_Fire_Rate = f_Burst_Fire_Rate;
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
int Weapon_Info::Get_Fire_Rate()
{
	return i_Fire_Rate;
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
int Weapon_Info::Get_Burst_Fire_Rate()
{
	return i_Burst_Fire_Rate;
}
bool Weapon_Info::Get_b_Burst_Fire()
{
	return b_Burst_Fire;
}

void Weapon_Info::Discharge(Vector3 position, Vector3 target, GameObject * object, SceneBase * _scene)
{
	if (b_Fire)
	{
		//CREATE PROJECTILE
		//I NEEDDSSS PROJECTILE
		//and player

		object->pos = position;
		object->vel = object->pos - target;
		object->scale.Set(3, 3, 3);
		object->mass = 3;
		object->active = true;
		b_Fire = false;
	}
}

void Weapon_Info::Discharge(Vector3 position, Vector3 target, SceneBase *_scene)
{
	if (b_Fire)
	{
		Projectile * aProjectile = Create::createProjectile(Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE, GameObject::GO_BALL, _scene);
		aProjectile->pos = position;
		aProjectile->vel = aProjectile->pos - target;
		aProjectile->scale.Set(3, 3, 3);
		aProjectile->mass = 3;
		aProjectile->active = true;
		/*	b_Fire = false;*/

	}
}

void Weapon_Info::castleAIDischarge(Vector3 position, float range, SceneBase * _scene)
{
	if (b_Fire)
	{
		Projectile * aProjectile = Create::createProjectile(Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE, GameObject::GO_BALL, _scene);
		aProjectile->typeOfMotion = Projectile::MOTION_TYPE::PROJECTILE_MOTION;
		aProjectile->pos = position;
		aProjectile->setInitVel(range);
		aProjectile->scale.Set(3, 3, 3);
		aProjectile->mass = 3;
		aProjectile->active = true;
		b_Fire = false;
	}
}

void Weapon_Info::castleAIDischarge(Vector3 position, Vector3 target, SceneBase * _scene)
{
	if (b_Fire)
	{
		Projectile * aProjectile = Create::createProjectile(Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE, GameObject::GO_BALL, _scene);
		aProjectile->typeOfMotion = Projectile::MOTION_TYPE::LINEAR_MOTION;
		aProjectile->pos = position;
		aProjectile->vel = target - aProjectile->pos;
		aProjectile->scale.Set(3, 3, 3);
		aProjectile->mass = 3;
		aProjectile->active = true;
		b_Fire = false;
	}

}

void Weapon_Info::PrintSelf(void)
{
}

//GameObject Weapon_Info::Get_OBJECT()
//{
//	GameObject &temp = tempObject;
//	return temp;
//}
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
