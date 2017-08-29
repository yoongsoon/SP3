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
			pos.Set(50, 60 + scale.y + (offset * 10), theScene->zaxis);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			m_groundLevel = theScene->m_worldHeight * 0.2f - scale.y;
			debugTag = "pWall";
			debugTag += to_string(offset);
			theScene->zaxis += 0.001f;
			break;
		case GameObject::GO_P_CASTLE:
			hitpoints = 500.f;
			meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
			pos.Set(15.f, 33.f, theScene->zaxis);
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			debugTag = "pCastle";
			cout << "castle " << pos.z << endl;
			cout << "castle2 " << scale.z << endl;
			theScene->zaxis += 0.001f;
			break;
		case GameObject::GO_AI_BRICK:
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set((theScene->m_worldWidth * 3) - 50.f, 60 + scale.y + (offset * 10), theScene->zaxis);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			m_groundLevel = theScene->m_worldHeight * 0.2f - scale.y;
			debugTag = "aiWall";
			debugTag += to_string(offset);
			theScene->zaxis += 0.001f;
			break;
		case GameObject::GO_AI_CASTLE:
			hitpoints = 500.f;
			pos.Set(15.f, 35.f, theScene->zaxis);
			meshValue = theScene->GEO_MINI_ENEMY_CASTLE;
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			debugTag = "aiCastle";
			theScene->zaxis += 0.001f;
			break;
		}
	case SceneBase::SC_02:
		switch (typeValue)
		{
		case GameObject::GO_P_BRICK:
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set(50, 60 + scale.y + (offset * 10), theScene->zaxis);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			m_groundLevel = theScene->m_worldHeight * 0.2f - scale.y;
			debugTag = "pWall";
			debugTag += to_string(offset);
			theScene->zaxis += 0.001f;
			break;
		case GameObject::GO_P_CASTLE:
			hitpoints = 500.f;
			meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
			pos.Set(15.f, 33.f, theScene->zaxis);
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			debugTag = "pCastle";
			cout << "castle " << pos.z << endl;
			cout << "castle2 " << scale.z << endl;
			theScene->zaxis += 0.001f;
			break;
		case GameObject::GO_AI_BRICK:
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set((theScene->m_worldWidth * 3) - 50.f, 60 + scale.y + (offset * 10), theScene->zaxis);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			m_groundLevel = theScene->m_worldHeight * 0.2f - scale.y;
			debugTag = "aiWall";
			debugTag += to_string(offset);
			theScene->zaxis += 0.001f;
			break;
		case GameObject::GO_AI_CASTLE:
			hitpoints = 500.f;
			pos.Set(15.f, 35.f, theScene->zaxis);
			meshValue = theScene->GEO_MINI_ENEMY_CASTLE;
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			debugTag = "aiCastle";
			theScene->zaxis += 0.001f;
			break;
		}
	}
	cout << debugTag << "Pos(xyz): " << pos << endl;
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
		SceneManager::getInstance()->SetActiveScene("LoseScene");
	}
		


	if (pos.y < -scale.y)
	{
		active = false;
	/*	SceneManager::getInstance()->SetActiveScene("LoseScene");*/
	}

	pos += vel;
	if (Application::IsKeyPressed('M'))
		cout << debugTag << " " << pos << endl;
}