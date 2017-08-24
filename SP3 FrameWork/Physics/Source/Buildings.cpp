#include "Buildings.h"
#include "SceneBase.h"
#include "Application.h"

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
			pos.Set(50, 60/* + scale.y + (offset * 10)*/, 1);
			wallPos.Set(pos.x, 20 + (scale.y) * initOffset, pos.z);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			if (offset == 1)
				debugTag = "thisone";
			else if (offset == 2)
				debugTag = "2ndone";
			break;
		case GameObject::GO_P_CASTLE:
			hitpoints = 500.f;
			meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
			pos.Set(15.f, 33.f, 1.f);
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			break;
		case GameObject::GO_AI_BRICK:
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set((theScene->m_worldWidth * 3) - 50.f, 40 + scale.y + (offset * 10), 1);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			m_canFall = true;
			break;
		case GameObject::GO_AI_CASTLE:
			hitpoints = 500.f;
			pos.Set(15.f, 35.f, 1.f);
			meshValue = theScene->GEO_MINI_ENEMY_CASTLE;
			scale.Set(30.f, 30.f, 1.f);
			m_canFall = false;
			break;
		}
	}
}

Buildings::~Buildings()
{

}

void Buildings::update()
{
	if (Application::IsKeyPressed('O') && !isPressed && debugTag == "thisone")
	{
		isPressed = true;
		hitpoints = 0;
	}
	if (Application::IsKeyPressed('P'))
		isPressed = false;

	if (m_canFall)
		vel.y += m_gravity * theScene->_dt * 0.04f;
	else
		vel.y = 0;
	
	if (type == GameObject::GO_P_BRICK || type == GameObject::GO_AI_BRICK)
	{
		if (pos.y > wallPos.y)
			m_canFall = true;
		else
			m_canFall = false;
	}

	// Cause buildings to fall out of screen
	if (hitpoints <= 0 && active)
	{
		m_canFall = true;
		wallPos.y -= scale.y;
	}
		

	if (pos.y < 0 - scale.y)
		active = false;

	pos += vel;
}