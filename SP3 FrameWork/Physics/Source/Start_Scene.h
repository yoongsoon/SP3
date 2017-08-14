#pragma once

#include "GameObject.h"
#include "SceneBase.h"

class SceneManager;

class START_Scene : public SceneBase
{

public:
	START_Scene(SceneManager * _scene);
	~START_Scene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();




protected:
	static START_Scene * sInstance; // The pointer to the object that gets registered


							   //Physics
	float m_speed;


};
