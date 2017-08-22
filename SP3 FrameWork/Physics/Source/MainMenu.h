#pragma once

#include "SceneBase.h"

class SceneManager;

class MainMenu : public SceneBase
{
public:
	enum MENU_MAIN
	{
		START_MENU,
		HIGHSCORE_MENU,
		QUIT_MENU,
	};

	MENU_MAIN  menuMain = START_MENU;

	MainMenu(SceneManager * _scene);
	~MainMenu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	static MainMenu * sInstance; 
	
};
