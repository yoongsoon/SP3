#pragma once

#include "GameObject.h"


class Castle : public GameObject
{
public:
	Castle(GAMEOBJECT_TYPE typeValue, SceneBase * scene, unsigned height);
	virtual ~Castle();

	void update();

private:
	float offset;
};
