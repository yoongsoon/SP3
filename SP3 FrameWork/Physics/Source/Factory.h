#pragma once

#include "GameObject.h"
#include "Projectile.h"

#include <map>
#include <vector>

//multimap allow insertion of multiple times of the same key  unlike map
typedef std::multimap<GameObject::GAMEOBJECT_TYPE, GameObject* > Mapping;
using std::vector;

class Factory
{
public:
	void createGameObject(GameObject * value);
	void destroyGameObject(GameObject * value);

	void updateGameObject();
	void renderGameObject();

	Mapping g_FactoryMap;
	vector<Projectile*> g_ProjectileVector;

	Factory();
	~Factory();

	Mapping::iterator gameObjectIter;
	vector<Projectile*>::iterator iteratorProject;

	bool isErased = false;
	bool isProjectileErased = false;

};