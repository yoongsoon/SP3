#pragma once
#include "WeaponInfo.h"
#include "Vector3.h"
#include "SoundEngine.h"
/*
#include "../FPSCamera.h"
#include "../GroundEntity.h"
#include "../WeaponInfo/WeaponInfo.h"
#include "../EntityManager.h"
#include "..//GenericEntity.h"*/

#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class SceneBase;

class PlayerInfo
{
protected:
	static PlayerInfo *s_instance;
	
public:
	static PlayerInfo *GetInstance()
	{
		if (!s_instance)
			s_instance = new PlayerInfo;
		return s_instance;
	}
	static bool DropInstance()
	{
		if (s_instance)
		{
			delete s_instance;
			s_instance = NULL;
			return true;
		}
		return false;
	}
	PlayerInfo(void);
	~PlayerInfo(void);

	// Initialise this class instance
	void Init(void);
	// Returns true if the player is on ground
	bool isOnGround(void);
	// Reset this player instance to default
	void Reset(void);

	// Set position
	void SetPos(const Vector3& pos);
	// Set target
	void SetTarget(const Vector3& target);
	// Set Up
	void SetUp(const Vector3& up);
	// Set the boundary for the player info
	void SetBoundary(Vector3 max, Vector3 min);
	// Set the terrain for the player info
	//void SetTerrain(GroundEntity* m_pTerrain);

	void SetWeapon(int w);
	// Get position
	Vector3 GetPos(void) const;
	// Get target
	Vector3 GetTarget(void) const;
	// Get Up
	Vector3 GetUp(void) const;
	//// Update
	void Update(double dt = 0.0333f);

	// Hardware Abstraction methods
	// Detect and process front / back movement on the controller
//	bool Move_FrontBack(const float deltaTime, const bool direction, const float speedMultiplier, std::list<GenericEntity*>obj, std::list<CEnemy3D*>Enemy);
	// Detect and process left / right movement on the controller
	//bool Move_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier, std::list<GenericEntity*>obj, std::list<CEnemy3D*>Enemy);
	// Detect and process look up / down on the controller
	//bool Look_UpDown(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	//// Detect and process look left / right on the controller
	//bool Look_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	//// Detect and process look up / down on the controller(Mouse)
	//bool Look_UpDownM(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	//// Detect and process look left / right on the controller(Mouse)
	//bool Look_LeftRightM(const float deltaTime, const bool direction, const float speedMultiplier = 1.0f);
	//// Stop sway
	//bool StopSway(const float deltaTime);

	// Reload current weapon
	bool ReloadWeapon(void);
	// Change current weapon
	bool ChangeWeapon(void);
	// Get Current Weapon
	int GetWeapon(void)const;
	//get elapsed time of cooldown
	double GetElapsedTime(void);
	// Discharge Primary Weapon
	bool DischargePrimaryWeapon(const float deltaTime);

	//bool DischargePPTEST(Vector3 position, Vector3 target, GameObject* tempObject, SceneBase *_scene);
	bool DischargePPTEST(Vector3 position, Vector3 target, SceneBase *_scene);
	// Constrain the position within the borders
	void Constrain(void);

	// Handling Camera
	//void AttachCamera(FPSCamera* _cameraPtr);
	//void DetachCamera();

	//GetProj
	//std::list<CProjectile*>GetProj();

	//Get Player AABB
	//CCollider GetplayerAABB();

	// Scrollable weapon switching
	Weapon_Info** weap_manager;
	int m_iCurrentWeapon;
	const int m_iNumOfWeapon = 3;
	Weapon_Info* primaryWeapon;
	//Weapon_Info* secondaryWeapon;

	//Health
	float health;

	bool colliding;

private:
	Vector3 defaultPosition, defaultTarget, defaultUp;
	Vector3 position, target, up;
	Vector3 maxBoundary, minBoundary;
	//GroundEntity* m_pTerrain;

	double m_dSpeed;
	double m_dAcceleration;

	double m_dElapsedTime;
	SceneBase *RyanFireLord;
};
