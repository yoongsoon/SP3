#include "Buildings.h"
#include "SceneBase.h"

Buildings::Buildings(GAMEOBJECT_TYPE typeValue, SceneBase * scene, unsigned offset) :GameObject(typeValue, scene)
{
	active = true;
	this->offset = offset;
	switch (theScene->m_sceneID)
	{
	case SceneBase::SC_01:
		switch (typeValue)
	case GameObject::GO_P_BRICK:
		hitpoints = 10;
		meshValue = theScene->GEO_BRICK;
		pos.Set(50, 40 + scale.y + (offset * 10), 1);
		dir.Set(0, 1, 0);
		scale.Set(12, 4, 1);
		break;
	case GameObject::GO_P_CASTLE:
		hitpoints = 500.f;
		pos.Set(15.f, 35.f, 1.f);
		meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
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

Buildings::~Buildings()
{

}

void Buildings::update()
{
	if (type == GameObject::GO_P_BRICK || type == GameObject::GO_AI_BRICK)
	{
		if (m_gEffect)
		{
			vel.y += m_gravity * theScene->_dt * 0.02f;
		}
		else
			vel.y = 0;
		
		if (m_gEffect && pos.y <= 20 && hitpoints > 0)
			m_gEffect = false;
		
		pos += vel;
		Mtx44 rotation;
		
	}

	// Cause buildings to fall out of screen
	if (hitpoints <= 0)
	{
		m_gEffect = true;
		
	}
	if (pos.y < 0 - scale.y)
		active = false;

	
		

	//Mtx44 rotation
}