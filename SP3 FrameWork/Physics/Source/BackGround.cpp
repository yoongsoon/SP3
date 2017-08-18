#include "BackGround.h"
#include "SceneBase.h"
#include "Application.h"

BackGround::BackGround(BACKGROUND_TYPE  _backGroundType, GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:typeOfBackGround(_backGroundType)
	,GameObject(typeValue , scene)
{
	active = true;

	switch (typeOfBackGround)
	{
	case BACK_GROUND_STAGE1:
	{
		meshValue = SceneBase::GEO_BACKGROUND;
	}
	break;
	}


	scale.Set(theScene->m_worldWidth *4, theScene->m_worldHeight, 1);
	pos.Set(theScene->m_worldWidth * 2, theScene->m_worldHeight * 0.5, 0);


}

BackGround::~BackGround()
{
}
