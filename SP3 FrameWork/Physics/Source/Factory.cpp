#include "Factory.h"

using std::make_pair;


void Factory::createGameObject(GameObject * value)
{
	g_FactoryMap.insert(make_pair(value->type, value));
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
}

