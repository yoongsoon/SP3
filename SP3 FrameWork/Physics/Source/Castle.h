#pragma once

#include "GameObject.h"


class Castle : public GameObject
{
public:
	Castle(GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~Castle();

	void update();

	float m_hp;
private:
	int hitpoints;
};
