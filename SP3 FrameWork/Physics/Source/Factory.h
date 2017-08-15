#pragma once

//#include "GameObject.h"
#include "Projectile.h"

#include <map>
#include <vector>

//multimap allow insertion of multiple times of the same key  unlike map
typedef std::multimap<GameObject::GAMEOBJECT_TYPE, GameObject* > Mapping;
typedef std::vector<Projectile*> Vectoring;

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
	Vectoring g_ProjectileVector;

	//Constructors/Destructors
	Factory();
	~Factory();

	//Iterators
	Mapping::iterator gameObjectIter;
	Vectoring::iterator iteratorProject;


};