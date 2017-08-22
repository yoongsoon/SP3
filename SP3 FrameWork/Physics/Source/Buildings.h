#pragma once

#include "GameObject.h"


class Buildings : public GameObject
{
public:
	Buildings(GAMEOBJECT_TYPE typeValue, SceneBase * scene, unsigned offset);
	virtual ~Buildings();

	void update();

private:
	float offset;
};
