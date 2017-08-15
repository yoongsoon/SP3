#pragma once

#include "GameObject.h"

class Projectile : public GameObject
{
public:
	enum PROJECTILE_TYPE
	{
		ARROW_PROJECTILE,
		ROCK_PROJECTILE,
		CANNON_BALL_PROJECTILE,
	};

	PROJECTILE_TYPE typeOfProjectile;

    // Constructor / Destructor
	Projectile(PROJECTILE_TYPE _typeofProjectile, GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~Projectile();

	//Update to run projectile logic
	virtual void update();

	// use to cap speed of projectile
	const float MAX_SPEED;
	// damage of projectile
	float m_damage;

private:
	float m_launchAngle;
};
