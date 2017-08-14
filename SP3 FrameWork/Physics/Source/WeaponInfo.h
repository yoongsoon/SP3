#pragma once

//include vetor3
//include where them projectile header???
#include <list>

class Weapon_Info
{
public:
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
	void Set_f_Fire_Rate(float);
	void Set_b_Fire(bool);

	void Set_d_Burst_timeBetweenShots(double);
	void Set_d_Burst_elapsedTime(double);
	void Set_f_Burst_Fire_Rate(float);
	void Set_b_Burst_Fire(bool);
	/*void fSet
		void fSet
		void fSet
		void fSet
		void fSet
		void fSet
		
		void fSet
		void fSet
		void fSet
		void fSet
		void fSet
		void fSet
*/

//_________________BURST_____FIRE_______________________________

	double Get_d_timeBetweenShots();
	double Get_d_elapsedTime();
	float Get_f_Fire_Rate();
	bool Get_b_Fire();

	double Get_d_Burst_timeBetweenShots();
	double Get_d_Burst_elapsedTime();
	float Get_f_Burst_Fire_Rate();
	bool Get_b_Burst_Fire();

	//prints details of weapon
	void PrintSelf(void);
	//getPRojectiles
//	std::list<Projectile*>GetProj();

private:
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



	//damage dealt by weapon
	//float Damage;
	//speed of projectile when shot
	//float Speed_of_Projectile;

	//time in between shots
	double d_timeBetweenShots;
	//elapsed time in between shots
	double d_elapsedTime;//starts Null
	//fire rate of triggered
	float f_Fire_Rate;
	//Flag availability to Fire
	bool b_Fire;
	//_________________BURST_____FIRE_______________________________

	//elapsed time in between projectiles
	double d_Burst_timeBetweenShots;
	//elapsed time of burst
	double d_Burst_elapsedTime;
	//fire rate of projectiles in between projectiles
	float f_Burst_Fire_Rate;
	//Flag if burst firing is done/available
	bool b_Burst_Fire;
	//std::list</*Projectile*/>bullets;

	//bool b_Fired
};
