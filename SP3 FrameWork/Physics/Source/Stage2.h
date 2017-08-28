#pragma once
#include "GameObject.h"
#include "SceneBase.h"

class SceneManager;

class Stage2 : public SceneBase
{

public:
	Stage2(SceneManager * _scene);
	~Stage2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void CreateFriendlySoldier();
	void CreateFriendlyArcher();
	void CreateFriendlyWizard();
protected:
	static Stage2 * sInstance; // The pointer to the object that gets registered

};
