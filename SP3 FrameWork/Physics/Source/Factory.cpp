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



void Factory::updateGameObject()
{
	// -------------------CODES TO DESRYOYED GAMEOBJECTS------------------------------//

	Mapping::iterator MapIt, MapEnd;
	MapEnd = g_FactoryMap.end();

	for (MapIt = g_FactoryMap.begin(); MapIt != MapEnd; MapIt++)
	{
		MapIt->second->update();
	}

	MapIt = g_FactoryMap.begin();
	while (MapIt != g_FactoryMap.end())
	{
		if (MapIt->second->isDestroyed == true)
		{
			 //Delete if done
			MapIt = g_FactoryMap.erase(MapIt);
			break;
		}
		else
		{
			// Move on otherwise
			++MapIt;
		}
	}



    // -------------------CODES TO DESRYOYED PROJECTILES------------------------------//
	Vectoring::iterator  VecIt, VecEnd;
	VecEnd = g_ProjectileVector.end();

	for (VecIt = g_ProjectileVector.begin(); VecIt != VecEnd; VecIt++)
	{
		(*VecIt)->update();
	}

	VecIt = g_ProjectileVector.begin();
	while (VecIt != g_ProjectileVector.end())
	{
		if ((*VecIt)->isDestroyed == true)
		{
			// Delete if done
			VecIt = g_ProjectileVector.erase(VecIt);
		}
		else
		{
			// Move on otherwise
			++VecIt;
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


	Vectoring::iterator iter = g_ProjectileVector.begin();

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
	en1 = new Enemy(GameObject::GO_ENEMY, theScene1,Enemy::E_SOLDIER);
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


	Vectoring::iterator iter;

	for (iter = g_ProjectileVector.begin(); iter != g_ProjectileVector.end(); ++iter)
	{
		delete (*iter);
		(*iter) = NULL;
	}

	g_ProjectileVector.clear();
}

