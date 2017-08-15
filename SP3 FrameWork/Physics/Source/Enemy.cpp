#include "Enemy.h"
#include "SceneBase.h"

Enemy::Enemy(GAMEOBJECT_TYPE GO_ENEMY, SceneBase * scene) :GameObject( GO_ENEMY, scene)
{
	meshValue = SceneBase::GEO_SOLDIER;
	StopToAttack = false;
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
	//destroy enemy when it ran out of hp
	if (hp <= 0)
	{
		isDestroyed = true;
		return;
	}


	if (enemyType == ENEMY_TYPE::E_SOLDIER)
	{
		if (StopToAttack)
		{
			vel = 0.0f;
		}
		else
		{
			pos += vel * theScene->_dt;
		}

	}
	else if (enemyType == ENEMY_TYPE::E_ARCHER)
	{

	}
	else if (enemyType == ENEMY_TYPE::E_WIZARD)
	{

	}
}