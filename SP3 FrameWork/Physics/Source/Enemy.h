#pragma once
#include <vector>
#include"GameObject.h"
#include "Vector3.h"
#include "timer.h"

using namespace std;

class Enemy : public GameObject
{
public:
	enum ENEMY_TYPE
	{
		E_SOLDIER,
		E_ARCHER,
		E_WIZARD
	};
	Enemy(GAMEOBJECT_TYPE GO_ENEMY,SceneBase *scene,ENEMY_TYPE meshvalue);
	~Enemy();
	virtual void update();

	bool StopToAttack;
	bool Attacked;
	float range;
	float hp;
	float damage;
	float attackcooldown;
	float spawncooldown;
	float cost;
	float timer;
	ENEMY_TYPE enemyType;
	StopWatch m_timer;
	float enemyMoveX;

private:
};