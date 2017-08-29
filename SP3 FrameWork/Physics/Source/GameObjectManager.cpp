#include "GameObjectManager.h"
#include "GameObject.h"
#include "SceneBase.h"
#include "Enemy.h"
#include "SoundEngine.h"

using std::next;


GameObjectManager::GameObjectManager(SceneBase * scene) :theScene(scene)
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


			//-----------CODES TO ENSURE it.second IS ALWAYS OF GO_ENEMY TYPE-------------//
			GameObject* goA = it->second;
			GameObject* goB = it2->second;

			//check projectile collision with other game object
			if (it->first != GameObject::GO_ENEMY)
			{
				if (it2->first != GameObject::GO_ENEMY)
					continue;

				//swap
				goA = it2->second;
				goB = it->second;
			}


			if (it2->first == GameObject::GO_PLAYER)
			{
				//if (static_cast <Enemy *>(it->second)->enemyType == Enemy::E_ARCHER && static_cast <Enemy *>(it2->second)->enemyType == Enemy::E_SOLDIER)
				//{

				//----------------------------------------------Enemy vs Player Units Collision----------------------------------------------------------------------------------------------------------------

				//Soldier is actually refering to player
				float player_position = static_cast <Enemy *>(it2->second)->pos.x;
				float player_range = static_cast <Enemy *>(it2->second)->range;
				float player_scale = static_cast <Enemy *>(it2->second)->scale.x;
				float player_hp = static_cast <Enemy *>(it2->second)->hp;
				float player_damage = static_cast <Enemy *>(it2->second)->damage;
				bool player_attacked = static_cast <Enemy *>(it2->second)->Attacked;
				bool player_stoptoattack = static_cast <Enemy *>(it2->second)->StopToAttack;
				bool player_active = static_cast <Enemy *>(it2->second)->active;
				//Archer is refering to enemy
				float enemy_position = static_cast <Enemy *>(it->second)->pos.x;
				float enemy_range = static_cast <Enemy *>(it->second)->range;
				float enemy_scale = static_cast <Enemy *>(it->second)->scale.x;
				float enemy_hp = static_cast <Enemy *>(it->second)->hp;
				float enemy_damage = static_cast <Enemy *>(it->second)->damage;
				bool enemy_attacked = static_cast <Enemy *>(it->second)->Attacked;
				bool enemy_stoptoattack = static_cast <Enemy *>(it->second)->StopToAttack;
				bool enemy_active = static_cast <Enemy *>(it->second)->active;


				if (enemy_active == true && player_active == true)
				{
					if (enemy_attacked == true && player_attacked == true)
					{
						if (CSoundEngine::getInstance()->isSoundAdded == false)
						{
							CSoundEngine::getInstance()->AddSound("Combat", "Sound//combat.ogg");
							CSoundEngine::getInstance()->isSoundAdded = true;
							CSoundEngine::getInstance()->PlayASound("Combat", false, false);
						}
					}
					//cout << player_position + player_range + player_scale - enemy_position << endl;
					//cout << enemy_position - enemy_range - enemy_scale - player_position << endl;
				}
				//if ((player_position > enemy_position) && ((player_position - player_range - player_scale - enemy_position) < 1.f) && player_active)//collision for player(for if enemy is on left side) && player is active
				//{

				//	if (enemy_active)//if enemy is active
				//	{
				//		if (!player_attacked)//if player has not attacked
				//		{
				//			enemy_hp -= player_damage; //enemy hp - player damage (attack)
				//			player_attacked = true;//start attack cooldown
				//			cout << "enemy " << enemy_hp << endl;
				//		}
				//		player_stoptoattack = true;//player stop moving to attack

				//	}
				//	else  //if enemy not active
				//	{
				//		//CSoundEngine::getInstance()->isSoundAdded = false;
				//		CSoundEngine::getInstance()->theCurrentSound->stop();
				//		player_stoptoattack = false;//player move after enemy died
				//	}
				//}
				if ((player_position < enemy_position) && ((player_position + player_range + player_scale - enemy_position) > -1.f) && player_active)//collision for player(for if enemy is on right side) && player is active
				{
					if (enemy_active)//if enemy is active
					{
						if (!player_attacked)//if player has not attacked
						{
							enemy_hp -= player_damage; //enemy hp - player damage (attack)
							player_attacked = true;//start attack cooldown
							//cout << "enemy " << enemy_hp << endl;
						}
						player_stoptoattack = true;//player stop moving to attack
					}
					else // if enemy not active
					{
						//CSoundEngine::getInstance()->isSoundAdded = false;
						CSoundEngine::getInstance()->theCurrentSound->stop();
						player_stoptoattack = false;//player move after enemy died
													 //cout << enemy
					}
				}
				if ((enemy_position > player_position) && ((enemy_position - enemy_range - enemy_scale - player_position) < 1.f) && enemy_active)//collision for player(for if enemy is on left side)
				{
					if (player_active)//if player is active
					{
						if (!enemy_attacked)//if enemy has not attacked
						{
							player_hp -= enemy_damage; //player hp - enemy damage (attack)
							enemy_attacked = true;//start attack cooldown
							//cout << "player " << player_hp << endl;
						}
						enemy_stoptoattack = true;//enemy stop moving to attack
					}
					else // if player not active
					{
						//CSoundEngine::getInstance()->isSoundAdded = false;
						CSoundEngine::getInstance()->theCurrentSound->stop();
						enemy_stoptoattack = false;//enemy move after enemy died
					}
				}
				//else if ((enemy_position < player_position) && ((enemy_position + enemy_range + enemy_scale - player_position) > 1.f) && enemy_active)//collision for player(for if enemy is on right side)
				//{
				//	if (player_active)//if player is active
				//	{
				//		if (!enemy_attacked)//if enemy has not attacked
				//		{
				//			player_hp -= enemy_damage; //player hp - enemy damage (attack)
				//			enemy_attacked = true;//start attack cooldown
				//			cout << "player " << player_hp << endl;
				//		}
				//		enemy_stoptoattack = true;//enemy stop moving to attack
				//	}
				//	else // if player not active
				//	{
				//		//CSoundEngine::getInstance()->isSoundAdded = false;
				//		CSoundEngine::getInstance()->theCurrentSound->stop();
				//		enemy_stoptoattack = false;//enemy move after enemy died
				//	}
				//}
				static_cast <Enemy *>(it2->second)->pos.x = player_position;
				static_cast <Enemy *>(it2->second)->range = player_range;
				static_cast <Enemy *>(it2->second)->scale.x = player_scale;
				static_cast <Enemy *>(it2->second)->hp = player_hp;
				static_cast <Enemy *>(it2->second)->damage = player_damage;
				static_cast <Enemy *>(it2->second)->Attacked = player_attacked;
				static_cast <Enemy *>(it2->second)->StopToAttack = player_stoptoattack;
				static_cast <Enemy *>(it2->second)->active = player_active;

				static_cast <Enemy *>(it->second)->pos.x = enemy_position;
				static_cast <Enemy *>(it->second)->range = enemy_range;
				static_cast <Enemy *>(it->second)->scale.x = enemy_scale;
				static_cast <Enemy *>(it->second)->hp = enemy_hp;
				static_cast <Enemy *>(it->second)->damage = enemy_damage;
				static_cast <Enemy *>(it->second)->Attacked = enemy_attacked;
				static_cast <Enemy *>(it->second)->StopToAttack = enemy_stoptoattack;
				static_cast <Enemy *>(it->second)->active = enemy_active;
				//------------------------------------------------------------------------------------------------------------------------------------------------------------------
				//}
			}


		}
		for (auto it2 = theScene->theFactory->g_BuildingsVector.begin(); it2 != theScene->theFactory->g_BuildingsVector.end(); it2++)
		{
			//check projectile collision with other game object
			if ((*it2)->type != GameObject::GO_P_CASTLE && (*it2)->type != GameObject::GO_P_BRICK && (*it2)->type != GameObject::GO_AI_BRICK && (*it2)->type != GameObject::GO_AI_CASTLE)
			{
				continue;
			}
			if (it->first != GameObject::GO_ENEMY && it->first != GameObject::GO_PLAYER)
			{
				continue;
			}

			//Soldier is actually refering to player
			float castle_position = (*it2)->pos.x;
			float castle_scale = (*it2)->scale.x;
			float castle_hp = (*it2)->hitpoints;
			bool castle_active = (*it2)->active;
			//Archer is refering to enemy
			float archer_position = static_cast <Enemy *>(it->second)->pos.x;
			float archer_range = static_cast <Enemy *>(it->second)->range;
			float archer_scale = static_cast <Enemy *>(it->second)->scale.x;
			float archer_hp = static_cast <Enemy *>(it->second)->hp;
			float archer_damage = static_cast <Enemy *>(it->second)->damage;
			bool archer_attacked = static_cast <Enemy *>(it->second)->Attacked;
			bool archer_stoptoattack = static_cast <Enemy *>(it->second)->StopToAttack;
			bool archer_active = static_cast <Enemy *>(it->second)->active;
			if ((it->first == GameObject::GO_ENEMY) && ((*it2)->type == GameObject::GO_P_CASTLE || (*it2)->type == GameObject::GO_P_BRICK))
			{
				//----------------------------------------------Enemy vs Player Castle & Bricks Collision----------------------------------------------------------------------------------------------------------------
				if ((archer_position > castle_position) && ((archer_position - archer_range - archer_scale - castle_position - (castle_scale / 2)) < 1.f) && archer_active)//collision for castle(for if archer is on left side)
				{
					if (castle_active && castle_hp > 0)//if castle is active
					{
						if (!archer_attacked)//if archer has not attacked
						{
							castle_hp -= archer_damage; //castle hp - archer damage (attack)
							archer_attacked = true;//start attack cooldown
							//cout << "castle " << castle_hp << endl;
						}
						archer_stoptoattack = true;//archer stop moving to attack
					}
					else // if castle not active
					{
						//CSoundEngine::getInstance()->isSoundAdded = false;
						CSoundEngine::getInstance()->theCurrentSound->stop();
						archer_stoptoattack = false;//archer move after enemy died
					}
				}
				(*it2)->pos.x = castle_position;
				(*it2)->scale.x = castle_scale;
				(*it2)->hitpoints = castle_hp;
				(*it2)->active = castle_active;
			}
			else if ((it->first == GameObject::GO_PLAYER) && ((*it2)->type == GameObject::GO_AI_CASTLE || (*it2)->type == GameObject::GO_AI_BRICK))
			{
				//----------------------------------------------Player vs Enemy Castle & Bricks Collision----------------------------------------------------------------------------------------------------------------
				if ((archer_position < castle_position) && ((archer_position + archer_range + archer_scale - castle_position + (castle_scale / 2)) > 1.f) && archer_active)//collision for castle(for if archer is on left side)
				{
					if (castle_active && castle_hp > 0)//if castle is active
					{
						if (!archer_attacked)//if archer has not attacked
						{
							castle_hp -= archer_damage; //castle hp - archer damage (attack)
							archer_attacked = true;//start attack cooldown
							//cout << "castle " << castle_hp << endl;
						}
						archer_stoptoattack = true;//archer stop moving to attack
					}
					else // if castle not active
					{
						//CSoundEngine::getInstance()->isSoundAdded = false;
						CSoundEngine::getInstance()->theCurrentSound->stop();
						archer_stoptoattack = false;//archer move after enemy died
					}
				}
				(*it2)->pos.x = castle_position;
				(*it2)->scale.x = castle_scale;
				(*it2)->hitpoints = castle_hp;
				(*it2)->active = castle_active;
			}
			//cout << "archer" << archer_position << endl;
			static_cast <Enemy *>(it->second)->pos.x = archer_position;
			static_cast <Enemy *>(it->second)->range = archer_range;
			static_cast <Enemy *>(it->second)->scale.x = archer_scale;
			static_cast <Enemy *>(it->second)->hp = archer_hp;
			static_cast <Enemy *>(it->second)->damage = archer_damage;
			static_cast <Enemy *>(it->second)->Attacked = archer_attacked;
			static_cast <Enemy *>(it->second)->StopToAttack = archer_stoptoattack;
			static_cast <Enemy *>(it->second)->active = archer_active;
		}
	}

}
