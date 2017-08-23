#pragma once

#include"GameObject.h"

class SceneBase;

class Player
{
public:
	Player();
	~Player();

	void setScene(SceneBase * scene);
	void update();
	float ReturnWallet();
	float ReturnEnemyWallet();
	float ReturnMaxWallet();
	void ReduceWalletAmount(float amount);
	void ReduceEnemyWalletAmount(float amount);
private:
	float wallet;
	float maxWallet;
	float cashamount;

	float enemywallet;
	float enemycashamount;
	SceneBase * theScene;
};