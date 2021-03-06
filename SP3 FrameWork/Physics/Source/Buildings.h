#pragma once

#include "GameObject.h"


class Buildings : public GameObject
{
public:
	Buildings(GAMEOBJECT_TYPE typeValue, SceneBase * scene, unsigned offset);
	virtual ~Buildings();
	enum AIStage
	{
		AI_STAGE1,
		AI_STAGE2,
		AI_STAGE3,
		AI_STAGE4,

	};
	void update();

	// need this function to save initialOffset in the data.txt
	float getInitialOffset() { return initOffset; }

protected:
	float initOffset;
	bool isPressed = false;
};
