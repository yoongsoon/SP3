#pragma once
#include "GameObject.h"
//#include "SceneBase.h"

class EnemyAI
{
public:
	enum AI_LEVEL
	{
		STAGE_1,
		STAGE_2,
		STAGE_3
	};

	AI_LEVEL  levelAI;

	EnemyAI(SceneBase * scene, AI_LEVEL _levelAi);
	~EnemyAI();
	virtual void Update(double dt);
	SceneBase * theScene;

	void CreateEnemySoldier();
	void CreateEnemyArcher();
	void CreateEnemyWizard();

private:
	float timer = 0.0f;
	bool surge = false;
	bool Stage1surge1 = true;
	bool Stage1surge2 = true;
};