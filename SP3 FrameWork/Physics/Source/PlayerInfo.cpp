#include "PlayerInfo.h"
#include <iostream>
#include "Cannon.h"
#include "Bow.h"
#include "Catapult.h"

#include "Application.h"
//#include "MouseController.h"
//#include "KeyboardController.h"
//#include "Mtx44.h"
//#include "../Projectile/Projectile.h"
//#include "../WeaponInfo/Pistol.h"
//#include "../WeaponInfo/AssualtRifle.h"
//#include "../Minimap/Minimap.h"

// Allocating and initializing CPlayerInfo's static data member.  
// The pointer is allocated but not the object's constructor.
PlayerInfo *PlayerInfo::s_instance = 0;

PlayerInfo::PlayerInfo(void)
	: m_dSpeed(40.0)
	, m_dAcceleration(10.0)
	, m_dElapsedTime(0.0)
	, primaryWeapon(NULL)
	//, secondaryWeapon(NULL)
	//, theCurrentPosture(STAND)
	, weap_manager(NULL)
	, m_iCurrentWeapon(0)
	, health(100)
	, colliding(false)
{
}

PlayerInfo::~PlayerInfo(void)
{
	if (weap_manager)
	{
		for (int i = 0; i < m_iNumOfWeapon; i++)
		{
			delete weap_manager[i];
		}
		delete[] weap_manager;
		weap_manager = NULL;
	}
	/*if (secondaryWeapon)
	{
		delete secondaryWeapon;
		secondaryWeapon = NULL;
	}*/
	if (primaryWeapon)
	{
		delete primaryWeapon;
		primaryWeapon = NULL;
	}
	//m_pTerrain = NULL;
}

// Initialise this class instance
void PlayerInfo::Init(void)
{
	// Set the default values
	defaultPosition.Set(0, 0, 10);
	defaultTarget.Set(0, 0, 0);
	defaultUp.Set(0, 1, 0);

	// Set the current values
	position.Set(0, 0, 10);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);

	// Set Boundary
	maxBoundary.Set(1, 1, 1);
	minBoundary.Set(-1, -1, -1);

	// Set the pistol as the primary weapon
	/*primaryWeapon = new Bow();
	primaryWeapon->Init();
*/
	weap_manager = new Weapon_Info*[m_iNumOfWeapon];
	//potato = new Catapult();
	//potato->Init();
	weap_manager[0] = new Bow();
	weap_manager[0]->Init();
	weap_manager[1] = new Cannon();
	weap_manager[1]->Init();
	weap_manager[2] = new Catapult();
	weap_manager[2]->Init();

}


// Returns true if the player is on ground
bool PlayerInfo::isOnGround(void)
{
		return true;
}

// Set position
void PlayerInfo::SetPos(const Vector3& pos)
{
	position = pos;
}

// Set target
void PlayerInfo::SetTarget(const Vector3& target)
{
	this->target = target;
}

// Set position
void PlayerInfo::SetUp(const Vector3& up)
{
	this->up = up;
}

// Set the boundary for the player info
//void PlayerInfo::SetBoundary(Vector3 max, Vector3 min)
//{
//	//maxBoundary = max;
//	//minBoundary = min;
//}


// Reset this player instance to default
void PlayerInfo::Reset(void)
{
	// Set the current values to default values
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;

	// Stop vertical movement too
	//StopVerticalMovement();
}


// Get position x of the player
Vector3 PlayerInfo::GetPos(void) const
{
	return position;
}

// Get target
Vector3 PlayerInfo::GetTarget(void) const
{
	return target;
}
// Get Up
Vector3 PlayerInfo::GetUp(void) const
{
	return up;
}

void PlayerInfo::SetWeapon(int w)
{
	m_iCurrentWeapon = w;
}

/********************************************************************************
Hero Update
********************************************************************************/
void PlayerInfo::Update(double dt)
{
	
	//if (primaryWeapon)
	//	primaryWeapon->Update(dt);
	/*if (secondaryWeapon)
		secondaryWeapon->Update(dt);*/
	
	
	if (weap_manager[m_iCurrentWeapon])
		weap_manager[m_iCurrentWeapon]->Update(dt);

}

// Get Current Weapon
//int PlayerInfo::GetWeapon(void) const
//{
//	return m_iCurrentWeapon;
//}

bool PlayerInfo::ChangeWeapon(void)
{
	return false;
}

// Discharge Primary Weapon
bool PlayerInfo::DischargePrimaryWeapon(const float deltaTime)
{
	//GameObject *tempObject = new  Projectile(Projectile::ARROW_PROJECTILE, GameObject::GO_PROJECTILE, this);

	//if (primaryWeapon)
	//{	//primaryWeapon->Discharge(position, target, this);
	//}
	/*if (weap_manager[m_iCurrentWeapon])
	{
		weap_manager[m_iCurrentWeapon]->Discharge(position, target, this);
		return true;
	}
*/
	return false;
}
// Discharge Primary Weapon
bool PlayerInfo::DischargePPTEST(Vector3 position, Vector3 target, SceneBase *_scene)
{
	//GameObject *tempObject = new  Projectile(Projectile::ARROW_PROJECTILE, GameObject::GO_PROJECTILE, this);

	/*if (primaryWeapon)
	{	
		primaryWeapon->Discharge(position, target,tempObject, _scene);
		return true;
	}
*/
	if (weap_manager[m_iCurrentWeapon])
	{
		weap_manager[m_iCurrentWeapon]->Discharge(position, target, _scene);
		return true;
	}

	return false;
}

// Constrain the position within the borders
void PlayerInfo::Constrain(void)
{
	
}

