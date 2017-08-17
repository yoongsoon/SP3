#include "MiniMap.h"
#include "MatrixStack.h"
#include "SceneBase.h"

MiniMap::MiniMap(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
{
	pos.Set(20, 50, 0);
	scale.Set(50, 50, 1);
}

MiniMap::~MiniMap()
{
}

void MiniMap::RenderUI()
{
	theScene->modelStack.PushMatrix();
	theScene->modelStack.Translate(pos.x, pos.y, pos.z);
	theScene->modelStack.Scale(scale.x, scale.y, scale.z);
	theScene->RenderMesh(theScene->meshList[SceneBase::GEO_MINI_ENEMY] , false);
	theScene->modelStack.PopMatrix();
}

