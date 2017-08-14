#pragma once

#include "GameObject.h"

#include <map>

//multimap allow insertion of multiple times of the same key  unlike map
typedef std::multimap<GameObject::GAMEOBJECT_TYPE, GameObject* > Mapping;

class Factory
{
public:
	void createGameObject(GameObject * value);
	void destroyGameObject(GameObject * value);

	void updateGameObject();
	void renderGameObject();

	Mapping g_FactoryMap;

	Factory();
	~Factory();

	Mapping::iterator gameObjectIter;
	bool isErased = false;

};