#pragma once

#include "GameObject.h"

class BackGround : public GameObject
{
public:
	enum BACKGROUND_TYPE
	{
	   BACK_GROUND_STAGE1,
	   BACK_GROUND_STAGE2,
	   BACK_GROUND_STAGE3,
	   BACK_GROUND_STAGE4,
	};

	BACKGROUND_TYPE typeOfBackGround;

	BackGround(BACKGROUND_TYPE  _backGroundType , GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~BackGround();

	virtual void update();
	
};
