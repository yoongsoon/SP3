#pragma once
#include <vector>
#include"GameObject.h"
#include "Vector3.h"
#include "timer.h"

using namespace std;

class PlayerTroop : public GameObject
{
public:
	enum PLAYER_TYPE
	{
		P_SOLDIER,
		P_ARCHER,
		P_WIZARD
	};
	PlayerTroop(GAMEOBJECT_TYPE GO_PLAYER, SceneBase *scene, PLAYER_TYPE meshvalue);
	~PlayerTroop();
	virtual void update();
	virtual void render();

	bool StopToAttack;
	bool Attacked;
	float range;
	float hp;
	float damage;
	float attackcooldown;
	float spawncooldown;
	float cost;
	float timer;
	PLAYER_TYPE playerType;
	StopWatch m_timer;

private:
};