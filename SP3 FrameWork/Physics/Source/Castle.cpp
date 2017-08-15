#include "SceneBase.h"

Castle::Castle(GAMEOBJECT_TYPE typeValue, SceneBase * scene) :GameObject(typeValue, scene)
{
	hitpoints = 10;
	meshValue = theScene->GEO_BRICK;
	active = true;
	pos.Set(theScene->m_worldWidth / 2, theScene->m_worldHeight / 2, 0);
	if (typeValue == GameObject::GO_BRICK)
	{
		dir.Set(0, 1, 0);
		scale.Set(4, 4, 1);
	}
		
}

Castle::~Castle()
{

}

void Castle::update()
{
	if (pos.y > 20)
		pos.y += m_gravity * theScene->_dt;
}