#pragma once

#include "GameObject.h"

class Cannon;

class AICastle : public GameObject
{
public:
	enum AIStage
	{
		AI_STAGE1,
		AI_STAGE2,
		AI_STAGE3,
		AI_STAGE4,

	};

	enum AI_STATE
	{
		AI_IDLE,
		AI_ATTACK,
	};

	AI_STATE stateOfAI;

	AICastle(GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~AICastle();

	virtual void update();
 
	// to detect range of castle to start attacking
	float m_castleRange;
	// cool down between each attack
	float m_coolDownTime;
	// bool to see whether the castle should fire
	bool b_isAttack;
	// default Hp
	float m_DefaultHp;

	Cannon * theAIweapon;

};