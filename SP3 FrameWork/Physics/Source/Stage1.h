#pragma once

#include "GameObject.h"
#include "SceneBase.h"
#include "Enemy.h"
class SceneManager;

class Stage1 : public SceneBase
{

public:
	Stage1(SceneManager * _scene);
	~Stage1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	static Stage1 * sInstance; // The pointer to the object that gets registered

							   //Physics
	float m_speed;
};
