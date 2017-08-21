#include "SceneBase.h"

Castle::Castle(GAMEOBJECT_TYPE typeValue, SceneBase * scene) :GameObject(typeValue, scene)
{
	active = true;
	
	if (typeValue == GameObject::GO_BRICK)
	{
		hitpoints = 10;
		pos.Set(theScene->m_worldWidth / 2, theScene->m_worldHeight / 2, 1);
		meshValue = theScene->GEO_BRICK;
		dir.Set(0, 1, 0);
		scale.Set(16, 4, 1);
	}
	else if (typeValue == GameObject::GO_CASTLE)
	{
		pos.Set(15.f, 50.f, 1.f);
		meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
		scale.Set(80.f, 80.f, 1.f);
	}
}

Castle::~Castle()
{

}

void Castle::update()
{
	if (type == GameObject::GO_BRICK)
	{
		if (pos.y > 20)
			vel.y += m_gravity * theScene->_dt;
		else
			vel.y = 0;
		pos += vel;
	}


	//Mtx44 rotation
}