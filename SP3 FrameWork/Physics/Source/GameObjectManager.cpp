#include "GameObjectManager.h"
#include "GameObject.h"
#include "SceneBase.h"
#include "Enemy.h"

using std::next;


GameObjectManager::GameObjectManager(SceneBase * scene):theScene(scene)
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
	Enemy_Enemy_Collision();
}

void GameObjectManager::Enemy_Enemy_Collision()
{
	for (auto it = theScene->theFactory->g_FactoryMap.begin(); it != theScene->theFactory->g_FactoryMap.end(); it++)
	{
		for (auto it2 = next(it); it2 != theScene->theFactory->g_FactoryMap.end(); it2++)
		{
			if (it == it2)
				continue;
			if (it->first == GameObject::GO_PLAYER && it2->first == GameObject::GO_ENEMY || it->first == GameObject::GO_ENEMY && it2->first == GameObject::GO_PLAYER)
			{
				//if (static_cast <Enemy *>(it->second)->enemyType == Enemy::E_ARCHER && static_cast <Enemy *>(it2->second)->enemyType == Enemy::E_SOLDIER)
				//{
//----------------------------------------------Enemy vs Player Units Collision----------------------------------------------------------------------------------------------------------------

					//Soldier is actually refering to player
					float soldier_position = static_cast <Enemy *>(it2->second)->pos.x;
					float soldier_range = static_cast <Enemy *>(it2->second)->range;
					float soldier_scale = static_cast <Enemy *>(it2->second)->scale.x;
					float soldier_hp = static_cast <Enemy *>(it2->second)->hp;
					float soldier_damage = static_cast <Enemy *>(it2->second)->damage;
					bool soldier_attacked = static_cast <Enemy *>(it2->second)->Attacked;
					bool soldier_stoptoattack = static_cast <Enemy *>(it2->second)->StopToAttack;
					bool soldier_active = static_cast <Enemy *>(it2->second)->active;
					//Archer is refering to enemy
					float archer_position = static_cast <Enemy *>(it->second)->pos.x;
					float archer_range = static_cast <Enemy *>(it->second)->range;
					float archer_scale = static_cast <Enemy *>(it->second)->scale.x;
					float archer_hp = static_cast <Enemy *>(it->second)->hp;
					float archer_damage = static_cast <Enemy *>(it->second)->damage;
					bool archer_attacked = static_cast <Enemy *>(it->second)->Attacked;
					bool archer_stoptoattack = static_cast <Enemy *>(it->second)->StopToAttack;
					bool archer_active = static_cast <Enemy *>(it->second)->active;

					if ((soldier_position > archer_position) && ((soldier_position - soldier_range - soldier_scale - archer_position) < 1.f) && soldier_active)//collision for soldier(for if archer is on left side) && soldier is active
					{
						
						if (archer_active)//if archer is active
						{
							if (!soldier_attacked)//if soldier has not attacked
							{
								archer_hp -= soldier_damage; //archer hp - soldier damage (attack)
								soldier_attacked = true;//start attack cooldown
								cout << "archer " << archer_hp << endl;
							}
							soldier_stoptoattack = true;//soldier stop moving to attack
							
						}
						else  //if archer not active
						{
							soldier_stoptoattack = false;//soldier move after enemy died
							/*alive = true;*/
							//Enemy::isDestroyed = true;
						}
					}
					else if ((soldier_position < archer_position) && ((soldier_position + soldier_range + soldier_scale - archer_position) > 1.f) && soldier_active)//collision for soldier(for if archer is on right side) && soldier is active
					{
						if (archer_active)//if archer is active
						{
							if (!soldier_attacked)//if soldier has not attacked
							{
								archer_hp -= soldier_damage; //archer hp - soldier damage (attack)
								soldier_attacked = true;//start attack cooldown
								cout << "archer " << archer_hp << endl;
							}
							soldier_stoptoattack = true;//soldier stop moving to attack
						}
						else // if archer not active
						{
							soldier_stoptoattack = false;//soldier move after enemy died
							//cout << archer
						}
					}
					if ((archer_position > soldier_position) && ((archer_position - archer_range - archer_scale - soldier_position) < 1.f) && archer_active)//collision for soldier(for if archer is on left side)
					{
						if (soldier_active)//if soldier is active
						{
							if (!archer_attacked)//if archer has not attacked
							{
								soldier_hp -= archer_damage; //soldier hp - archer damage (attack)
								archer_attacked = true;//start attack cooldown
								cout << "soldier " << soldier_hp << endl;
							}
							archer_stoptoattack = true;//archer stop moving to attack
						}
						else // if soldier not active
						{
							archer_stoptoattack = false;//archer move after enemy died
						}
					}
					else if ((archer_position < soldier_position) && ((archer_position + archer_range + archer_scale - soldier_position) > 1.f) && archer_active)//collision for soldier(for if archer is on right side)
					{
						if (soldier_active)//if soldier is active
						{
							if (!archer_attacked)//if archer has not attacked
							{
								soldier_hp -= archer_damage; //soldier hp - archer damage (attack)
								archer_attacked = true;//start attack cooldown
								cout << "soldier " << soldier_hp << endl;
							}
							archer_stoptoattack = true;//archer stop moving to attack
						}
						else // if soldier not active
						{
							archer_stoptoattack = false;//archer move after enemy died
						}
					}
					static_cast <Enemy *>(it2->second)->pos.x = soldier_position;
					static_cast <Enemy *>(it2->second)->range = soldier_range;
					static_cast <Enemy *>(it2->second)->scale.x = soldier_scale;
					static_cast <Enemy *>(it2->second)->hp = soldier_hp;
					static_cast <Enemy *>(it2->second)->damage = soldier_damage;
					static_cast <Enemy *>(it2->second)->Attacked = soldier_attacked;
					static_cast <Enemy *>(it2->second)->StopToAttack = soldier_stoptoattack;
					static_cast <Enemy *>(it2->second)->active = soldier_active;

					static_cast <Enemy *>(it->second)->pos.x = archer_position;
					static_cast <Enemy *>(it->second)->range = archer_range;
					static_cast <Enemy *>(it->second)->scale.x = archer_scale;
					static_cast <Enemy *>(it->second)->hp = archer_hp;
					static_cast <Enemy *>(it->second)->damage = archer_damage;
					static_cast <Enemy *>(it->second)->Attacked = archer_attacked;
					static_cast <Enemy *>(it->second)->StopToAttack = archer_stoptoattack;
					static_cast <Enemy *>(it->second)->active = archer_active;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------
				//}
			}
		}

	}
}
