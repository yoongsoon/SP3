#pragma once


#include "Vector3.h"
#include "Projectile.h"
#include "GameObject.h"
//include where them projectile header???
#include <list>

class SceneBase;

class Weapon_Info
{
public:
	enum WEAPON_TYPE
	{
		TYPE_BOW,
		TYPE_CANNON,
		TYPE_CATAPULT
	};

	enum FIRE_MODE
	{
		NORMAL_FIRE,
		BURST_FIRE,
	};

	FIRE_MODE FireMode;
	WEAPON_TYPE WeaponType;
	Projectile::PROJECTILE_TYPE projectile_type;

	void setFireMode(FIRE_MODE FireMode);
	int bulletCount = 0;

	Weapon_Info();
	~Weapon_Info();
	//virtual ~Weapon_Info();
	virtual void Init(void);
	void Update(const double dt);
	//void Discharge(Vector3 position, Vector3 target, PlayerInfo _source = NULL);

//	void f_Set_
//	void b_Set_
//	void d_Set_
//	void i_Set_
//	float f_get_
//	bool b_get_
//	int i_get_

	void Set_d_timeBetweenShots(double);
	void Set_d_elapsedTime(double);
	void Set_Fire_Rate(int);
	void Set_b_Fire(bool);

	void Set_d_Burst_timeBetweenShots(double);
	void Set_d_Burst_elapsedTime(double);
	void Set_Burst_Fire_Rate(int);
	void Set_b_Burst_Fire(bool);
	

//_________________BURST_____FIRE_______________________________

	double Get_d_timeBetweenShots();
	double Get_d_elapsedTime();
	int Get_Fire_Rate();
	bool Get_b_Fire();

	double Get_d_Burst_timeBetweenShots();
	double Get_d_Burst_elapsedTime();
	int Get_Burst_Fire_Rate();
	bool Get_b_Burst_Fire();

	//GameObject Get_OBJECT();

	//void Discharge(Vector3 position,Vector3 target,)
	//void Discharge(Vector3 position, Vector3 target, CPlayerInfo* _source = NULL);
	//void Discharge(Vector3 position, Vector3 target,SceneBase * _scene);
	void Discharge(Vector3 position, Vector3 target,GameObject * object,SceneBase * _scene);

	// ------------Discharge for player---------------------//
	void Discharge(Vector3 position, Vector3 target, SceneBase * _scene);

    //-------------Discharge for Castle AI----------------------//
	//  position of projectile , range of projectile , scene  (PROJECTILE_MOTION)
	void castleAIDischarge(Vector3 position,  float range, SceneBase * _scene );
	// position of projectile ,target of projectile , scene (LINEAR MOTION)
	void castleAIDischarge(Vector3 position, Vector3 target, SceneBase * _scene);


	//prints details of weapon
	void PrintSelf(void);
	//getPRojectiles
//	std::list<Projectile*>GetProj();

protected:
	//since infinite ammo
	/*
	//number of ammunition in a magazine
	int i_magRounds;
	//maximum number of ammunition a magazine can carry
	int i_maxMagRounds;
	//current ammunition inside the current clip
	int i_totalRounds;
	//maximum ammunition player currently carrying
	int i_maxTotalRounds;

	*/

	//GameObject tempObject;
	GameObject *tempObject;
	//damage dealt by weapon
	//float Damage;
	//speed of projectile when shot
	//float Speed_of_Projectile;

	//time in between shots
	double d_timeBetweenShots;
	//elapsed time in between shots
	double d_elapsedTime;//starts Null
	//fire rate of triggered
	int i_Fire_Rate;
	//Flag availability to Fire
	bool b_Fire;
	//_________________BURST_____FIRE_______________________________

	//elapsed time in between projectiles
	double d_Burst_timeBetweenShots;
	//elapsed time of burst
	double d_Burst_elapsedTime;
	//fire rate of projectiles in between projectiles
	int i_Burst_Fire_Rate;
	//Flag if burst firing is done/available
	bool b_Burst_Fire;
	//std::list</*Projectile*/>bullets;
	int i_bulletcount;
	int i_maxbullet;

	Vector3 pin_position;
	Vector3 pin_target;
	SceneBase *pin_scene;
	float pin_range;
};
