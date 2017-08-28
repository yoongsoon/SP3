#include "Buildings.h"
#include "SceneBase.h"
#include "Application.h"
#include "SceneManager.h"

Buildings::Buildings(GAMEOBJECT_TYPE typeValue, SceneBase * scene, unsigned offset) :GameObject(typeValue, scene)
{
	active = true;
	this->initOffset = offset;
	switch (theScene->m_sceneID)
	{
	case SceneBase::SC_01:
		switch (typeValue)
		{
		case GameObject::GO_P_BRICK:
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set(50, theScene->m_worldHeight * 0.5 + (offset * 10), 1);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			m_groundLevel = theScene->m_worldHeight * 0.2f;
			debugTag = "pWall";
			debugTag += to_string(offset);
			break;
		case GameObject::GO_P_CASTLE:
			hitpoints = 500.f;
			meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
			pos.Set(15.f, 33.f, 1.f);
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			debugTag = "pCastle";
			break;
		case GameObject::GO_AI_BRICK:
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set((theScene->m_worldWidth * 3) - 50.f, theScene->m_worldHeight * 0.5 + (offset * 10), 1);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			m_groundLevel = theScene->m_worldHeight * 0.2f;
			debugTag = "aiWall";
			debugTag += to_string(offset);
			break;
		case GameObject::GO_AI_CASTLE:
			hitpoints = 500.f;
			pos.Set(15.f, 35.f, 1.f);
			meshValue = theScene->GEO_MINI_ENEMY_CASTLE;
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			debugTag = "aiCastle";
			break;
		}
	}
}

Buildings::~Buildings()
{

}

void Buildings::update()
{
	// Ensures object is affected by gravity if can fall
	if (m_canFall)
		vel.y += m_gravity * theScene->_dt * 0.1f;
	else
		vel.y = 0;
	
	if (type == GameObject::GO_P_BRICK || type == GameObject::GO_AI_BRICK)
	{
		if (pos.y - scale.y * 0.5f > m_groundLevel)
			m_canFall = true;
		else
			m_canFall = false;
	}
	
	// Cause buildings to fall out of screen
	if (hitpoints <= 0 && active)
	{
		m_canFall = true;
		m_groundLevel = -scale.y - 1;
	}
		


	if (pos.y < -scale.y)
	{
		active = false;
	/*	SceneManager::getInstance()->SetActiveScene("LoseScene");*/
	}

	pos += vel;
}