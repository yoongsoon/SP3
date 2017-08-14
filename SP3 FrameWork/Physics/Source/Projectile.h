#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~Projectile();

	virtual void update();

	const float MAX_SPEED;

private:
	float m_launchAngle;
};
