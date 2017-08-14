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
	Enemy(GAMEOBJECT_TYPE GO_ENEMY,SceneBase *scene);
	~Enemy();
	virtual void update();

	bool StopToAttack;
	float range;
	float hp;
	float damage;
	float cooldown;
	ENEMY_TYPE enemyType;
	StopWatch m_timer;
private:
};