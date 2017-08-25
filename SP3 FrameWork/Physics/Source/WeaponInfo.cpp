#include "WeaponInfo.h"
#include "Projectile.h"
#include "GameObject.h"

void Weapon_Info::setFireMode(FIRE_MODE FireMode)
{
	this->FireMode = FireMode;
}

Weapon_Info::Weapon_Info()
	:d_timeBetweenShots(0.5)
	, d_elapsedTime(0.0)
	, i_Fire_Rate(1)
	, b_Fire(true)
	, d_Burst_timeBetweenShots(0.2)
	, d_Burst_elapsedTime(0.0)
	, i_Burst_Fire_Rate(2)
	, b_Burst_Fire(false)
	, i_bulletcount(0)
	,i_maxbullet(3)
	, FireMode(NORMAL_FIRE)
{

	switch (WeaponType)
	{
	case Weapon_Info::TYPE_BOW:
		projectile_type = Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE;
		break;
	case Weapon_Info::TYPE_CANNON:
		projectile_type = Projectile::PROJECTILE_TYPE::CANNON_BALL_PROJECTILE;
		break;
	case Weapon_Info::TYPE_CATAPULT:
		projectile_type = Projectile::PROJECTILE_TYPE::ROCK_PROJECTILE;
		break;
	default:
		break;
	}
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

	i_bulletcount = 0;
	i_maxbullet = 3;
}
void Weapon_Info::Update(const double dt)
{
	if (!b_Fire && b_Burst_Fire)
	{
		d_elapsedTime += dt;
		
	}
	if (d_elapsedTime > d_timeBetweenShots)
	{
		b_Fire = true;
		d_elapsedTime = 0.0;
	}
	

	if (!b_Burst_Fire)
	{
		d_Burst_elapsedTime += dt;
	}
	if (d_Burst_elapsedTime > d_Burst_timeBetweenShots)
	{
		b_Fire = true;
		b_Burst_Fire = true;
		d_Burst_elapsedTime = 0.0;
		if (pin_position != NULL)
		{
			Discharge(pin_position, pin_target, pin_scene);
		}
		else if (pin_AIrange!=NULL)
		{
			castleAIDischarge(pin_AIposition, pin_AIrange, pin_AIscene);
		}
		else if (pin_AItarget!=NULL)
		{
			castleAIDischarge(pin_AIposition, pin_AItarget, pin_AIscene);
		}
		
	}
	if (i_bulletcount>=i_maxbullet)
	{
		i_bulletcount = 0;
		b_Burst_Fire = true;
		d_elapsedTime = 0.0;

		pin_position = NULL;
		pin_AIposition = NULL;
		pin_target = NULL;
		pin_AItarget = NULL;
		pin_scene = NULL;
		pin_AIscene = NULL;
		pin_AIrange = NULL;
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

void Weapon_Info::Set_Max_BulletCount(int b)
{
	i_maxbullet = b;
}

int Weapon_Info::Get_Max_BulletCount()
{
	return i_maxbullet;
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
		//object->mass = 35;
		object->active = true;
		b_Fire = false;
	}
}
//player discharge
void Weapon_Info::Discharge(Vector3 position, Vector3 target, SceneBase *_scene)
{
	if (b_Fire)
	{
		//
		if (b_Burst_Fire)
		{
			pin_position = position;
			pin_target = target;
			pin_scene = _scene;
			//
			//needs get projectile type to change projectiles or maybe weapon type
			Projectile * aProjectile = Create::createProjectile(projectile_type, GameObject::GO_P_PROJECTILE, _scene);
			//Projectile * aProjectile = Create::createProjectile(Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE, GameObject::GO_PROJECTILE, _scene);
			aProjectile->typeOfMotion = Projectile::PROJECTILE_MOTION;
			aProjectile->whoseProjectile = Projectile::PROJECTILE_WHOSE::PLAYER_PROJECTILE;
			//where projectile shoots from
			aProjectile->pos = Vector3(20,50,5);
			aProjectile->rotateZ = Math::RadianToDegree(atan2f(position.y - target.y, position.x - target.x));
			//aProjectile->pos = position;
			//aProjectile->pos.z = 5;
			aProjectile->vel = position - target;
			aProjectile->scale.Set(3, 3, 3);
			//aProjectile->mass = 3;
			aProjectile->active = true;
			//
			i_bulletcount++;
			b_Burst_Fire = false;
			b_Fire = false;
		}
	}
}

void Weapon_Info::castleAIDischarge(Vector3 position, float range, SceneBase * _scene)
{
	if (b_Fire)
	{
		//
		if (b_Burst_Fire)
		{
			pin_AIposition = position;
			//pin_target = target;
			pin_AIrange = range;
			pin_AIscene = _scene;
			Projectile * aProjectile = Create::createProjectile(Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE, GameObject::GO_AI_PROJECTILE, _scene);
			aProjectile->typeOfMotion = Projectile::MOTION_TYPE::PROJECTILE_MOTION;
			aProjectile->whoseProjectile = Projectile::PROJECTILE_WHOSE::ENEMY_PROJECTILE;
			aProjectile->pos = position;
			aProjectile->setInitVel(range);
			aProjectile->scale.Set(3, 3, 3);
			aProjectile->mass = 3;
			aProjectile->active = true;
			b_Fire = false;
			//
			i_bulletcount++;
			b_Burst_Fire = false;
			b_Fire = false;
		}

	}
}

void Weapon_Info::castleAIDischarge(Vector3 position, Vector3 target, SceneBase * _scene)
{
	if (b_Fire)
	{

		if (b_Burst_Fire)
		{
			pin_AIposition = position;
			pin_AItarget = target;
			pin_AIscene = _scene;
			Projectile * aProjectile = Create::createProjectile(Projectile::PROJECTILE_TYPE::ARROW_PROJECTILE, GameObject::GO_AI_PROJECTILE, _scene);
			aProjectile->typeOfMotion = Projectile::MOTION_TYPE::LINEAR_MOTION;
			aProjectile->whoseProjectile = Projectile::PROJECTILE_WHOSE::ENEMY_PROJECTILE;
			aProjectile->pos = position;
			aProjectile->vel = target - position;
			aProjectile->scale.Set(3, 3, 3);
			//aProjectile->mass = 3;
			aProjectile->active = true;
		//	b_Fire = false;
			i_bulletcount++;
			b_Burst_Fire = false;
			b_Fire = false;
		}
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
