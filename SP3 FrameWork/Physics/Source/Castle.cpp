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
		break;
	}
	
}

Castle::~Castle()
{

}

void Castle::update()
{
	if (m_gEffect)
		vel.y += m_gravity * theScene->_dt * 0.5f;
	else
		vel.y = 0;
	pos += vel;

	if (pos.y <= 20)
		m_gEffect = false;
	if (hitpoints <= 0)
		active = false;

	//Mtx44 rotation
}