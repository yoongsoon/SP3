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
		topLeft.Set(pos.x - (scale.x * 0.5f), pos.y + (scale.y * 0.5f), 0);
		topRight.Set(pos.x + (scale.x * 0.5f), pos.y + (scale.y * 0.5f), 0);
		bottomLeft.Set(pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f), 0);
		bottomRight.Set(pos.x + (scale.x * 0.5f), pos.y - (scale.y * 0.5f), 0);
	}
	cout << topLeft << topRight << bottomLeft << bottomRight << endl;
}

Castle::~Castle()
{

}

void Castle::update()
{
	if (pos.y > 20)
		vel.y += m_gravity * theScene->_dt;
	else
		vel.y = 0;
	pos += vel;
	topLeft = (pos.x - scale.x * 0.5f, pos.y + scale.y * 0.5f, 0);
	topRight = (pos.x + scale.x * 0.5f, pos.y + scale.y * 0.5f, 0);
	bottomLeft = (pos.x - scale.x * 0.5f, pos.y - scale.y * 0.5f, 0);
	bottomRight = (pos.x + scale.x * 0.5f, pos.y - scale.y * 0.5f, 0);

	

}