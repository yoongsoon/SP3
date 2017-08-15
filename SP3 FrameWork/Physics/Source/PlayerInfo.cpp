#include "PlayerInfo.h"
#include <iostream>
#include "Cannon.h"
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
	//, attachedCamera(NULL)
	//, m_pTerrain(NULL)
	//, primaryWeapon(NULL)
	//, secondaryWeapon(NULL)
	//, theCurrentPosture(STAND)
//	, weaponManager(NULL)
	, m_iCurrentWeapon(0)
	//, m_fCameraSwayAngle(0.0f)
	//, m_fCameraSwayDeltaAngle(0.1f)
	//, m_fCameraSwayAngle_LeftLimit(-0.3f)
	//, m_fCameraSwayAngle_RightLimit(0.3f)
	//, m_bCameraSwayDirection(false)
	, health(100)
	, colliding(false)
{
}

PlayerInfo::~PlayerInfo(void)
{
	/*if (weaponManager)
	{
		for (int i = 0; i < m_iNumOfWeapon; i++)
		{
			delete weaponManager[i];
		}
		delete[] weaponManager;
		weaponManager = NULL;
	}
	if (secondaryWeapon)
	{
		delete secondaryWeapon;
		secondaryWeapon = NULL;
	}
	if (primaryWeapon)
	{
		delete primaryWeapon;
		primaryWeapon = NULL;
	}*/
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
	//primaryWeapon = new Cannon();
	//primaryWeapon->Init();

	//weaponManager = new Weapon_Info*[m_iNumOfWeapon];
	//weaponManager[0] = new Cannon();
	//weaponManager[0]->Init();

	/*weaponManager[1] = new CAssualtRifle();
	weaponManager[1]->Init();
*/
	//Player Collision
	//playerAABB.SetPAABB(Vector3(5, 5, 5), GetPos());

	//m_fCameraSwayAngle = 0.0f;
	//m_fCameraSwayDeltaAngle = 1.0f;
	//m_fCameraSwayAngle_LeftLimit = -5.0f;
	//m_fCameraSwayAngle_RightLimit = 5.0f;
	//m_bCameraSwayDirection = false;
}

// Returns true if the player is on ground
bool PlayerInfo::isOnGround(void)
{
	//if (m_bJumpUpwards == false && m_bFallDownwards == false && position.y == m_pTerrain->GetTerrainHeight(position))
		return true;

	//return false;
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
void PlayerInfo::SetBoundary(Vector3 max, Vector3 min)
{
	//maxBoundary = max;
	//minBoundary = min;
}

// Set the terrain for the player info
//void PlayerInfo::SetTerrain(GroundEntity* m_pTerrain)
//{
//	if (m_pTerrain != NULL)
//	{
//		this->m_pTerrain = m_pTerrain;
//
//		SetBoundary(this->m_pTerrain->GetMaxBoundary(), this->m_pTerrain->GetMinBoundary());
//	}
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

/********************************************************************************
Hero Update
********************************************************************************/
void PlayerInfo::Update(double dt)
{
	
	/*if (primaryWeapon)
		primaryWeapon->Update(dt);
	if (secondaryWeapon)
		secondaryWeapon->Update(dt);*/
	/*if (weaponManager[m_iCurrentWeapon])
		weaponManager[m_iCurrentWeapon]->Update(dt);
*/
}

// Detect and process front / back movement on the controller
//bool PlayerInfo::Move_FrontBack(const float deltaTime, const bool direction, const float speedMultiplier, std::list<GenericEntity*>obj, std::list<CEnemy3D*>Enemy)
//{
//	colliding = false;
//	// Add camera sway
//	if (m_bCameraSwayDirection == false)
//	{
//		m_fCameraSwayAngle -= m_fCameraSwayDeltaAngle;
//		if (m_fCameraSwayAngle < m_fCameraSwayAngle_LeftLimit * speedMultiplier)
//			m_bCameraSwayDirection = !m_bCameraSwayDirection;
//	}
//	else
//	{
//		m_fCameraSwayAngle += m_fCameraSwayDeltaAngle;
//		if (m_fCameraSwayAngle > m_fCameraSwayAngle_RightLimit * speedMultiplier)
//			m_bCameraSwayDirection = !m_bCameraSwayDirection;
//	}
//
//	Vector3 viewVector = (target - position).Normalized();
//
//	//Collision check
//	bool move = false;
//
//	if (direction)
//	{
//		//position += viewVector * (float)m_dSpeed * speedMultiplier * (float)deltaTime;
//		if ((theCurrentPosture == STAND) && (KeyboardController::GetInstance()->IsKeyDown(VK_SHIFT)))
//		{
//			for (auto &i : obj)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 2.0f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			for (auto &i : Enemy)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 2.0f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			if (!move)
//				position += viewVector * (float)m_dSpeed * 2.0f * (float)deltaTime;
//		}
//		else if (theCurrentPosture == CROUCH)
//		{
//			for (auto &i : obj)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 0.75f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			for (auto &i : Enemy)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 0.75f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			if (!move)
//				position += viewVector * (float)m_dSpeed * 0.75f * (float)deltaTime;
//		}
//		else if (theCurrentPosture == PRONE)
//		{
//			for (auto &i : obj)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 0.25f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			for (auto &i : Enemy)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 0.25f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			if (!move)
//				position += viewVector * (float)m_dSpeed * 0.25f * (float)deltaTime;
//		}
//		else
//		{
//			for (auto &i : obj)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 2.0f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			for (auto &i : Enemy)
//			{
//				Vector3 temppos = position;
//				Vector3 forward = temppos += viewVector * (float)m_dSpeed * 2.0f * (float)deltaTime;
//				//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//				if (!i->IsDone())
//					move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//				if (move)
//				{
//					health--;
//					colliding = true;
//					return false;
//				}
//			}
//
//			if (!move)
//				position += viewVector * (float)m_dSpeed * (float)deltaTime;
//		}
//		//	 Constrain the position
//		Constrain();
//		// Update the target
//		target = position + viewVector;
//
//		return true;
//	}
//	else
//	{
//		for (auto &i : obj)
//		{
//			Vector3 temppos = position;
//			Vector3 forward = temppos -= viewVector * (float)m_dSpeed * (float)deltaTime;
//			//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//			if (!i->IsDone())
//				move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//			if (move)
//			{
//				health--;
//				colliding = true;
//				return false;
//			}
//		}
//
//		for (auto &i : Enemy)
//		{
//			Vector3 temppos = position;
//			Vector3 forward = temppos -= viewVector * (float)m_dSpeed * (float)deltaTime;
//			//move = EntityManager::GetInstance()->CheckOverlap(playerAABB.GetMinAABB(), playerAABB.GetMaxAABB(), i->GetMinAABB(), i->GetMaxAABB());
//
//			if (!i->IsDone())
//				move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//			if (move)
//			{
//				health--;
//				colliding = true;
//				return false;
//			}
//		}
//
//		if (!move)
//			position -= viewVector * (float)m_dSpeed * (float)deltaTime;
//
//		//	 Constrain the position
//		Constrain();
//		// Update the target
//		target = position + viewVector;
//		return true;
//	}
//
//	return false;
//}
// Detect and process left / right movement on the controller
//bool PlayerInfo::Move_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier, std::list<GenericEntity*>obj, std::list<CEnemy3D*>Enemy)
//{
//	Vector3 viewVector = target - position;
//	Vector3 rightUV;
//
//	//Collision check
//	bool move = false;
//
//	if (direction)
//	{
//		rightUV = (viewVector.Normalized()).Cross(up);
//		rightUV.y = 0;
//		rightUV.Normalize();
//
//		for (auto &i : obj)
//		{
//			Vector3 temppos = position;
//			Vector3 forward = temppos -= rightUV * (float)m_dSpeed * deltaTime;
//
//			if (!i->IsDone())
//				move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//			if (move)
//			{
//				health--;
//				colliding = true;
//				return false;
//			}
//		}
//
//		for (auto &i : Enemy)
//		{
//			Vector3 temppos = position;
//			Vector3 forward = temppos -= rightUV * (float)m_dSpeed * deltaTime;
//
//			if (!i->IsDone())
//				move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//			if (move)
//			{
//				health--;
//				colliding = true;
//				return false;
//			}
//		}
//
//		if (!move)
//			position -= rightUV * (float)m_dSpeed * deltaTime;
//
//		//	 Constrain the position
//		Constrain();
//		// Update the target
//		target = position + viewVector;
//
//		return true;
//	}
//	else
//	{
//		rightUV = (viewVector.Normalized()).Cross(up);
//		rightUV.y = 0;
//		rightUV.Normalize();
//
//		for (auto &i : obj)
//		{
//			Vector3 temppos = position;
//			Vector3 forward = temppos += rightUV * (float)m_dSpeed * deltaTime;
//
//			if (!i->IsDone())
//				move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//			if (move)
//			{
//				health--;
//				colliding = true;
//				return false;
//			}
//		}
//
//		for (auto &i : Enemy)
//		{
//			Vector3 temppos = position;
//			Vector3 forward = temppos += rightUV * (float)m_dSpeed * deltaTime;
//
//			if (!i->IsDone())
//				move = EntityManager::GetInstance()->pointtoAABB(temppos, forward, i);
//
//			if (move)
//			{
//				health--;
//				colliding = true;
//				return false;
//			}
//		}
//
//		if (!move)
//			position += rightUV * (float)m_dSpeed * deltaTime;
//
//		//	 Constrain the position
//		Constrain();
//		// Update the target
//		target = position + viewVector;
//		return true;
//	}
//	return false;
//}

//bool PlayerInfo::Look_UpDown(const float deltaTime, const bool direction, const float speedMultiplier)
//{
//	if (speedMultiplier == 0.0f)
//		return false;
//
//	Vector3 viewUV = (target - position).Normalized();
//	Vector3 rightUV;
//
//	if (!direction)
//	{
//		float pitch = (float)(-m_dSpeed * speedMultiplier * (float)deltaTime);
//		rightUV = viewUV.Cross(up);
//		rightUV.y = 0;
//		rightUV.Normalize();
//		up = rightUV.Cross(viewUV).Normalized();
//		Mtx44 rotation;
//		rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
//		viewUV = rotation * viewUV;
//		target = position + viewUV;
//	}
//	else
//	{
//		float pitch = (float)(m_dSpeed * speedMultiplier * (float)deltaTime);
//		rightUV = viewUV.Cross(up);
//		rightUV.y = 0;
//		rightUV.Normalize();
//		up = rightUV.Cross(viewUV).Normalized();
//		Mtx44 rotation;
//		rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
//		viewUV = rotation * viewUV;
//		target = position + viewUV;
//	}
//
//	return true;
//}
//
//bool PlayerInfo::Look_LeftRight(const float deltaTime, const bool direction, const float speedMultiplier)
//{
//	if (speedMultiplier == 0.0f)
//		return false;
//
//	Vector3 viewUV = (target - position).Normalized();
//	Vector3 rightUV;
//
//	if (!direction)
//	{
//		float yaw = (float)-m_dSpeed * speedMultiplier * (float)deltaTime;
//		Mtx44 rotation;
//		rotation.SetToRotation(yaw, 0, 1, 0);
//		viewUV = rotation * viewUV;
//		target = position + viewUV;
//		rightUV = viewUV.Cross(up);
//		rightUV.y = 0;
//		rightUV.Normalize();
//		up = rightUV.Cross(viewUV).Normalized();
//	}
//	else
//	{
//		float yaw = (float)m_dSpeed * speedMultiplier * (float)deltaTime;
//		Mtx44 rotation;
//		rotation.SetToRotation(yaw, 0, 1, 0);
//		viewUV = rotation * viewUV;
//		target = position + viewUV;
//		rightUV = viewUV.Cross(up);
//		rightUV.y = 0;
//		rightUV.Normalize();
//		up = rightUV.Cross(viewUV).Normalized();
//	}
//
//	return true;
//}
//
//// masterrace
//bool PlayerInfo::Look_UpDownM(const float deltaTime, const bool direction, const float speedMultiplier)
//{
//	if (speedMultiplier == 0.0f)
//		return false;
//
//	Vector3 viewUV = (target - position).Normalized();
//	Vector3 rightUV;
//
//	float pitch = (float)(-m_dSpeed * speedMultiplier * (float)deltaTime);
//	rightUV = viewUV.Cross(up);
//	rightUV.y = 0;
//	rightUV.Normalize();
//	up = rightUV.Cross(viewUV).Normalized();
//	Mtx44 rotation;
//	rotation.SetToRotation(pitch, rightUV.x, rightUV.y, rightUV.z);
//
//	if ((rotation * viewUV).y > 0.8 && pitch > 0)
//		return false;
//	if ((rotation * viewUV).y < -0.7 && pitch < 0)
//		return false;
//
//	viewUV = rotation * viewUV;
//	target = position + viewUV;
//
//	return true;
//}
//
//bool PlayerInfo::Look_LeftRightM(const float deltaTime, const bool direction, const float speedMultiplier)
//{
//	if (speedMultiplier == 0.0f)
//		return false;
//
//	Vector3 viewUV = (target - position).Normalized();
//	Vector3 rightUV;
//
//	float yaw = (float)-m_dSpeed * speedMultiplier * (float)deltaTime;
//	Mtx44 rotation;
//	rotation.SetToRotation(yaw, 0, 1, 0);
//	viewUV = rotation * viewUV;
//	target = position + viewUV;
//	rightUV = viewUV.Cross(up);
//	rightUV.y = 0;
//	rightUV.Normalize();
//	up = rightUV.Cross(viewUV).Normalized();
//
//	return true;
//}
//
//// Stop sway
//bool PlayerInfo::StopSway(const float deltaTime)
//{
//	m_bCameraSwayDirection = false;
//	m_fCameraSwayAngle = 0.0f;
//	up = Vector3(0.0f, 1.0f, 0.0f);
//	return true;
//}

// Reload current weapon
//bool PlayerInfo::ReloadWeapon(void)
//{
//	if (weaponManager[m_iCurrentWeapon])
//	{
//		weaponManager[m_iCurrentWeapon]->Reload();
//		return true;
//	}
//	return false;
//}

// Change current weapon
//bool PlayerInfo::ChangeWeapon(void)
//{
//	if (MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) != m_iCurrentWeapon)
//	{
//		if ((MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) >= 0) &&
//			(MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET) < m_iNumOfWeapon))
//		{
//			m_iCurrentWeapon = MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE_YOFFSET);
//		}
//	}
//	return true;
//}
//
//bool PlayerInfo::ChangeWeaponK(void)
//{
//	m_iCurrentWeapon++;
//	MouseController::GetInstance()->SetScrollStatus(m_iCurrentWeapon);
//
//	if (m_iCurrentWeapon > 1)
//	{
//		m_iCurrentWeapon = 0;
//		MouseController::GetInstance()->SetScrollStatus(m_iCurrentWeapon);
//	}
//
//	return true;
//}

// Get Current Weapon
int PlayerInfo::GetWeapon(void) const
{
	return m_iCurrentWeapon;
}

// Discharge Primary Weapon
bool PlayerInfo::DischargePrimaryWeapon(const float deltaTime)
{
	//if (primaryWeapon)
	//	primaryWeapon->Discharge(position, target, this);

	//if (weaponManager[m_iCurrentWeapon])
	//{
	//	weaponManager[m_iCurrentWeapon]->Discharge(position, target, this);
		return true;
	//}

	//return false;
}

// Constrain the position within the borders
void PlayerInfo::Constrain(void)
{
	// Constrain player within the boundary
	//if (position.x > maxBoundary.x - 1.0f)
	//{
	//	position.x = maxBoundary.x - 1.0f;
	//	CCameraEffects::GetInstance()->SetStatus_BloodScreen(true);
	//}
	//if (position.y > maxBoundary.y - 1.0f)
	//{
	//	position.y = maxBoundary.y - 1.0f;
	//	m_dJumpSpeed = 0.0;
	//	m_bJumpUpwards = false;
	//	m_dFallSpeed = 0.0;
	//	m_bFallDownwards = true;
	//	m_dElapsedTime = 0.0;
	//}
	//if (position.z > maxBoundary.z - 1.0f)
	//{
	//	position.z = maxBoundary.z - 1.0f;
	//	CCameraEffects::GetInstance()->SetStatus_BloodScreen(true);
	//}
	//if (position.x < minBoundary.x + 1.0f)
	//{
	//	position.x = minBoundary.x + 1.0f;
	//	CCameraEffects::GetInstance()->SetStatus_BloodScreen(true);
	//}
	//if (position.y < minBoundary.y + 1.0f)
	//	position.y = minBoundary.y + 1.0f;
	//if (position.z < minBoundary.z + 1.0f)
	//{
	//	position.z = minBoundary.z + 1.0f;
	//	CCameraEffects::GetInstance()->SetStatus_BloodScreen(true);
	//}

	//// if the player is not jumping nor falling, then adjust his y position
	//if ((!m_bJumpUpwards) && (!m_bFallDownwards))
	//{
	//	Vector3 viewDirection = target - position;
	//	switch (theCurrentPosture)
	//	{
	//	case STAND:
	//		position.y = m_pTerrain->GetTerrainHeight(Vector3(position.x, 0.0f, position.z));
	//		target = position + viewDirection;
	//		break;
	//	case CROUCH:
	//		position.y = m_pTerrain->GetTerrainHeight(Vector3(position.x, 0.0f, position.z)) - 5.0f;
	//		target.y = position.y + viewDirection.y;
	//		break;
	//	case PRONE:
	//		position.y = m_pTerrain->GetTerrainHeight(Vector3(position.x, 0.0f, position.z)) - 8.0f;
	//		target.y = position.y + viewDirection.y;
	//		break;
	//	default:
	//		// if the y position is not equal to terrain height at that position, 
	//		// then update y position to the terrain height
	//		if (position.y != m_pTerrain->GetTerrainHeight(position))
	//			position.y = m_pTerrain->GetTerrainHeight(position);
	//		break;
	//	}
	//}
}

//std::list<Projectile*> PlayerInfo::GetProj()
//{
//	return weaponManager[m_iCurrentWeapon]->GetProj();
//}

//CCollider PlayerInfo::GetplayerAABB()
//{
//	return playerAABB;
//}
