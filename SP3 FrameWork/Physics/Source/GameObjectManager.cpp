#include "GameObjectManager.h"
#include "GameObject.h"
#include "SceneBase.h"
#include "Enemy.h"

using std::next;

GameObjectManager::GameObjectManager(SceneBase * scene)
	:theScene(scene)

{

}

GameObjectManager::~GameObjectManager()
{
	if (theScene)
	{
		delete theScene;
		theScene = NULL;
	}


}

void GameObjectManager::update()
{
	for (auto it = theScene->theFactory->g_FactoryMap.begin(); it != theScene->theFactory->g_FactoryMap.end(); it ++)
	{
		
		for (auto it2 = next(it); it2 != theScene->theFactory->g_FactoryMap.end(); it2++)	
		{
			if (it == it2)
				continue;

			if (it->first == GameObject::GO_ENEMY && it2->first == GameObject::GO_ENEMY)
			{
		
				if (static_cast <Enemy *>(it->second)->enemyType == Enemy::E_ARCHER && static_cast <Enemy *>(it2->second)->enemyType == Enemy::E_SOLDIER)
				{
					cout << "hi" << endl;

					if ((static_cast <Enemy *>(it2->second)->pos.x + static_cast <Enemy *>(it2->second)->range) - (static_cast <Enemy *>(it->second)->pos.x) < 1.f ||
						(static_cast <Enemy *>(it2->second)->pos.x - static_cast <Enemy *>(it2->second)->range) - (static_cast <Enemy *>(it->second)->pos.x) < 1.f)
					{
						//static_cast <Enemy *>(it2->second)->hp -= static_cast <Enemy *>(it->second)->damage;
						it2->second->rotateX += 30.f;
						static_cast <Enemy *>(it2->second)->StopToAttack = true;
						cout << "bpoom" << endl;
					}
					//if ((static_cast <Enemy *>(it2->second)->pos.x + static_cast <Enemy *>(it2->second)->range) == (static_cast <Enemy *>(it->second)->pos.x))
					//{
					//	//static_cast <Enemy *>(it->second)->hp -= static_cast <Enemy *>(it2->second)->damage;
					//}
				}
			}
		}

	}

}
