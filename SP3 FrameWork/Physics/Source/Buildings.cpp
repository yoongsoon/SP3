#include "Buildings.h"
#include "SceneBase.h"
#include "Application.h"

Buildings::Buildings(GAMEOBJECT_TYPE typeValue, SceneBase * scene, unsigned offset) :GameObject(typeValue, scene)
{
	active = true;
	this->offset = offset;
	switch (theScene->m_sceneID)
	{
	case SceneBase::SC_01:
		switch (typeValue)
		{
		case GameObject::GO_P_BRICK:
			hitpoints = 10 - offset;
			meshValue = theScene->GEO_BRICK;
			pos.Set(50, 40 + scale.y + (offset * 10), 1);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			canFall = true;
			break;
		case GameObject::GO_P_CASTLE:
			hitpoints = 500.f;
			meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
			pos.Set(15.f, 35.f, 1.f);
			scale.Set(30.f, 30.f, 1.f);
			break;
		case GameObject::GO_AI_BRICK:
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set(50, 40 + scale.y + (offset * 10), 1);
			dir.Set(0, 1, 0);
			scale.Set(12, 4, 1);
			break;
		case GameObject::GO_AI_CASTLE:
			hitpoints = 500.f;
			pos.Set(15.f, 35.f, 1.f);
			meshValue = theScene->GEO_MINI_ENEMY_CASTLE;
			scale.Set(30.f, 30.f, 1.f);
			break;
		}
	}
}

Buildings::~Buildings()
{

}

void Buildings::update()
{
	if (Application::IsKeyPressed('O') && !isPressed)
	{
		isPressed = true;
		if (hitpoints > 8)
			hitpoints = 0;
		else
			--hitpoints;
	}
	if (Application::IsKeyPressed('P'))
		isPressed = false;

	if (type == GameObject::GO_P_BRICK || type == GameObject::GO_AI_BRICK)
	{
		if (m_gEffect && canFall)
			vel.y += m_gravity * theScene->_dt * 0.03f;
		else
			vel.y = 0;

		if (m_gEffect && pos.y <= 20 && hitpoints > 0)
			canFall = false;
		else
			canFall = true;
	}
	

	// Cause buildings to fall out of screen
	if (hitpoints <= 0 && active)
		canFall = true;

	if (pos.y < 0 - scale.y)
		active = false;

	pos += vel;
}