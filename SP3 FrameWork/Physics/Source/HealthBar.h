#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "SceneBase.h"

class HealthBar: public GameObject
{
	enum BAR_TYPE
	{
		CASTLE_BAR,
		TROOP_BAR
	};

	HealthBar(GAMEOBJECT_TYPE GO_ENEMY, SceneBase * scene, GameObject * go);
	~HealthBar();
};