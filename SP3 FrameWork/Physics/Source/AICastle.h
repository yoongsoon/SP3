#pragma once

#include "GameObject.h"
#include "WeaponInfo.h"

//class Cannon;

class AICastle : public GameObject
{
public:
	AICastle(GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~AICastle();

	virtual void update();
 
	// to detect range of castle to start attacking
	float m_castleRange;
	// cool down between each attack
	float m_coolDownTime;
	// bool to see whether the castle should fire
	bool b_isAttack;
	// default Hp
	float m_DefaultHp;
	
	bool isDead = false;
	//use weapon info is better
	//Cannon * theAIweapon;
	Weapon_Info * theAIweapon;
	//use this if AI has more than 1 weapon on castle vv (refer to player info weapon manager)
	//Weapon_Info**AIweapons;
	//int totanumberAIweapons;
	//int currAIweapon
};