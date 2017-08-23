#include "Factory.h"
#include "SceneBase.h"

using std::make_pair;


void Factory::createGameObject(GameObject * value)
{
	// push every game object except projectile into the map container
	if (value->type == GameObject::GO_P_PROJECTILE || value->type == GameObject::GO_AI_PROJECTILE)
		g_ProjectileVector.push_back(static_cast<Projectile*>(value));
	else if (value->type == GameObject::GO_P_BRICK || value->type == GameObject::GO_AI_BRICK || value->type == GameObject::GO_P_CASTLE || value->type == GameObject::GO_AI_CASTLE)
		g_BuildingsVector.push_back(static_cast<Buildings*>(value));
	else   // push projectile into the vector container
		g_FactoryMap.insert(make_pair(value->type, value));

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
		ProjectileVector::iterator  VecIt, VecEnd;
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
	
		// -------------------CODES TO DESTROY BUILDINGS------------------------------//
		BuildingsVector::iterator  VecIt2, VecEnd2;
		VecEnd2 = g_BuildingsVector.end();

		for (VecIt2 = g_BuildingsVector.begin(); VecIt2 != VecEnd2; ++VecIt2)
		{
			(*VecIt2)->update();
		}

		VecIt2 = g_BuildingsVector.begin();
		while (VecIt2 != g_BuildingsVector.end())
		{
			if ((*VecIt2)->isDestroyed == true)
			{
				// Delete if done
				VecIt2 = g_BuildingsVector.erase(VecIt2);
			}
			else
			{
				// Move on otherwise
				++VecIt2;
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


	ProjectileVector::iterator iter = g_ProjectileVector.begin();

	for (iter; iter != g_ProjectileVector.end(); ++iter)
	{
		if ((*iter)->active)
		{
			(*iter)->render();
		}
	}

	BuildingsVector ::iterator iter2 = g_BuildingsVector.begin();

	for (iter2; iter2 != g_BuildingsVector.end(); ++iter2)
	{
		if ((*iter2)->active)
		{
			(*iter2)->render();
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


	ProjectileVector::iterator iter;

	for (iter = g_ProjectileVector.begin(); iter != g_ProjectileVector.end(); ++iter)
	{
		delete (*iter);
		(*iter) = NULL;
	}

	g_ProjectileVector.clear();

	BuildingsVector::iterator iter2;

	for (iter2 = g_BuildingsVector.begin(); iter2 != g_BuildingsVector.end(); ++iter2)
	{
		delete (*iter2);
		(*iter) = NULL;
	}

	g_BuildingsVector.clear();
}

