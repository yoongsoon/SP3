#pragma once
#pragma once

#include "SceneBase.h"

class SceneManager;

class LoseScene : public SceneBase
{
public:
	enum LOSE_SCENE
	{
		RESTART_LOSE,
		MAIN_MENU_LOSE,
		QUIT_LOSE,
	};

	LOSE_SCENE  sceneLost = RESTART_LOSE;

	LoseScene(SceneManager * _scene);
	~LoseScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	static LoseScene * sInstance;

};
