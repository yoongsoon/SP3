#include "Factory.h"

using std::make_pair;


void Factory::createGameObject(GameObject * value)
{
	// push every game object except projectile into the map container
	if (value->type != GameObject::GO_PROJECTILE)
		g_FactoryMap.insert(make_pair(value->type, value));
	else   // push projectile into the vector container
		g_ProjectileVector.push_back(static_cast<Projectile*>(value));

}

void Factory::destroyGameObject(GameObject * value)
{
	gameObjectIter = g_FactoryMap.begin();

	for (gameObjectIter; gameObjectIter != g_FactoryMap.end();)
	{
		if (gameObjectIter->first == value->type)
		{
			//Erase return the next valid iterator
			gameObjectIter = g_FactoryMap.erase(gameObjectIter);
			isErased = true;
			return;
		}
		else
		{
			gameObjectIter++;
		}
	}


	iteratorProject = g_ProjectileVector.begin();

	for (iteratorProject; iteratorProject != g_ProjectileVector.end();)
	{
		if ((*iteratorProject) == static_cast<Projectile*>(value))
		{
			//Erase return the next valid iterator
			iteratorProject = g_ProjectileVector.erase(iteratorProject);
			isProjectileErased = true;
			return;
		}
		else
		{
			iteratorProject++;
		}
	}

}

void Factory::updateGameObject()
{
	gameObjectIter = g_FactoryMap.begin();
	for (gameObjectIter; gameObjectIter != g_FactoryMap.end();)
	{
		gameObjectIter->second->update();

		if (isErased == false)
		{
			gameObjectIter++;
		}
		else
		{
			//one of the GameObject * is Erased , so reset bool isErased
			isErased = false;
		}
	}


	iteratorProject = g_ProjectileVector.begin();
	for (iteratorProject; iteratorProject != g_ProjectileVector.end();)
	{
		(*iteratorProject)->update();

		if (isProjectileErased == false)
		{
			iteratorProject++;
		}
		else
		{
			//one of the GameObject * is Erased , so reset bool isErased
			isProjectileErased = false;
		}
	}

}


void Factory::renderGameObject()
{
	Mapping::iterator it = g_FactoryMap.begin();

	for (it; it != g_FactoryMap.end(); it++)
	{
		if (it->second->active)  //<--- only render if GameObject *  's active is set to true
		{
			it->second->render();
		}
	}


	vector<Projectile*>::iterator iter = g_ProjectileVector.begin();

	for (iter; iter != g_ProjectileVector.end(); ++iter)
	{
		if ((*iter)->active)
		{
			(*iter)->render();
		}
	}


}



Factory::Factory()
{

}

Factory::~Factory()
{
	Mapping::iterator it;

	for (it = g_FactoryMap.begin(); it != g_FactoryMap.end(); ++it)
	{
		//delet GameObject *
		delete it->second;
		it->second = NULL;
	}

	//Clear the map
	g_FactoryMap.clear();


	vector<Projectile*>::iterator iter;

	for (iter = g_ProjectileVector.begin(); iter != g_ProjectileVector.end(); ++iter)
	{
		delete (*iter);
		(*iter) = NULL;
	}

	g_ProjectileVector.clear();
}

