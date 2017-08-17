#pragma once
#include "SceneBase.h"
#include"GameObject.h"
class Player
{
public:
	Player();
	~Player();

	void setScene(SceneBase * scene);
	void update();
	float ReturnWallet();
	float ReturnEnemyWallet();
	void ReduceWalletAmount(float amount);
	void ReduceEnemyWalletAmount(float amount);
private:
	float wallet;
	float cashamount;

	float enemywallet;
	float enemycashamount;
	SceneBase * theScene;
};