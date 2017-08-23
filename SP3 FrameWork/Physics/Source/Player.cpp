#include "Player.h"
#include "SceneBase.h"

Player::Player()
{
	cashamount = 10.f;
	wallet = 200.f;
	maxWallet = wallet;
	enemycashamount = 10.f;
	enemywallet = 200.f;
}

Player::~Player()
{
}

void Player::setScene(SceneBase * scene)
{
	theScene = scene;
}

void Player::update()
{
	wallet += cashamount * theScene->_dt;
	enemywallet += enemycashamount * theScene->_dt;
	//cout << wallet << endl;
}

float Player::ReturnWallet()
{
	return wallet;
}

float Player::ReturnEnemyWallet()
{
	return enemywallet;
}

float Player::ReturnMaxWallet()
{
	return maxWallet;
}

void Player::ReduceWalletAmount(float amount)
{
	wallet -= amount;
}

void Player::ReduceEnemyWalletAmount(float amount)
{
	enemywallet -= amount;
}
