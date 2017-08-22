#include "SceneBase.h"

Castle::Castle(GAMEOBJECT_TYPE typeValue, SceneBase * scene, unsigned offset) :GameObject(typeValue, scene)
{
	active = true;
	this->offset = offset;
	switch (theScene->m_sceneID)
	{
	case SceneBase::SC_01:
		if (typeValue == GameObject::GO_BRICK)
		{
			hitpoints = 10;
			meshValue = theScene->GEO_BRICK;
			pos.Set(50, 40 + scale.y + (offset * 10), 1);
			dir.Set(0, 1, 0);
			scale.Set(12, 3, 1);
		}
		else if (typeValue == GameObject::GO_CASTLE)
		{
			hitpoints = 500.f;
			pos.Set(15.f, 50.f, 0.5f);
			meshValue = theScene->GEO_MINI_PLAYER_CASTLE;
			scale.Set(30.f, 30.f, 1.f);
		}
		break;
	}
}

Castle::~Castle()
{

}

void Castle::update()
{
	if (type == GameObject::GO_BRICK)
	{
		if (m_gEffect)
			vel.y += m_gravity * theScene->_dt * 0.5f;
		else
			vel.y = 0;
		pos += vel;
	}

	if (pos.y <= 20)
		m_gEffect = false;
	if (hitpoints <= 0)
		active = false;

	//Mtx44 rotation
}