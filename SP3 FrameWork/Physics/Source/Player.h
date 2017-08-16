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
private:
	float wallet;
	float cashamount;

	SceneBase * theScene;
};