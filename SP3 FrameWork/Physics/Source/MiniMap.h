#pragma once

#include "Mesh.h"
#include "GameObject.h"

class MiniMap : public GameObject
{
public:
	MiniMap(GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~MiniMap();

	 void Update();
	 virtual void RenderUI();

};