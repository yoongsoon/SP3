#pragma once

#include "SceneBase.h"

class SceneManager;

class Credits_Menu : public SceneBase
{
public:
	//enum MENU_MAIN
	//{
	//	START_MENU,
	//	HIGHSCORE_MENU,
	//	QUIT_MENU,
	//};

	//MENU_MAIN  menuMain = START_MENU;

	Credits_Menu(SceneManager * _scene);
	~Credits_Menu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	static Credits_Menu * sInstance;

};
