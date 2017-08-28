#pragma once

//#include "GameObject.h"
#include "Projectile.h"
#include "GameObjectManager.h"
#include <map>
#include <vector>
#include "Enemy.h"
#include "Buildings.h"
 
//multimap allow insertion of multiple times of the same key  unlike map
typedef std::multimap<GameObject::GAMEOBJECT_TYPE, GameObject* > Mapping;
typedef std::vector<Projectile*> ProjectileVector;
typedef std::vector<Buildings*> BuildingsVector;

class Factory
{
public:
	//Create 
	void createGameObject(GameObject * value);
	//TO destroy object just called object->isDestroyed = true

	void updateGameObject();
	void renderGameObject();

	//Containers
	Mapping g_FactoryMap;
	ProjectileVector g_ProjectileVector;
	BuildingsVector g_BuildingsVector;
	//Constructors/Destructors
	Factory();
	~Factory();

	//Iterators
	Mapping::iterator gameObjectIter;
	ProjectileVector::iterator projectileIterator;
	BuildingsVector::iterator buildingsIterator;

};