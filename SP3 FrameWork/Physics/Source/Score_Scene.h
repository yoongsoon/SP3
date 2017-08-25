#pragma once

#include "GameObject.h"
#include "SceneBase.h"

class SceneManager;

class Score_Scene : public SceneBase
{

public:
	Score_Scene(SceneManager * _scene);
	~Score_Scene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();




protected:
	static Score_Scene * sInstance; // The pointer to the object that gets registered


									//Physics
	float m_speed;


};
