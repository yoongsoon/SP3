#include "Player.h"

Player::Player()
{
	cashamount = 5.f;
	wallet = 0.f;
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
}
