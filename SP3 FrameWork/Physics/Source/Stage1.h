#pragma once
#include "PlayerInfo.h"
#include "GameObject.h"
#include "SceneBase.h"
#include "Enemy.h"
#include "WeaponInfo.h"
#include "PlayerTroops.h"
#include "Player.h"
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

	//void CreatePlayerWeap();
	void CreateEnemySoldier();
	void CreateEnemyArcher();
	void CreateEnemyWizard();
	void CreateFriendlySoldier();
	void CreateFriendlyArcher();
	void CreateFriendlyWizard();
protected:
	static Stage1 * sInstance; // The pointer to the object that gets registered
	//player(aka the player on tower)
	/*
	contains 
	health
	weapons
	prjectile*/
	PlayerInfo* thePlayer;
	//switch weapons
	Weapon_Info** weap_manager;
	int curr_weapon = 0;
	//Weapon_Info* potato;
				
	//Physics
	float m_speed;
	Player *theplayer;
	Enemy *enemy;
	SceneBase * scenebase;

	bool ghost_exist = false;
	bool release_ghost_exist = false;
	bool M_ghost_exist = false;
	bool canPredict;

	//for text
	int a;
	double e;
	string player_weap_choice;
	string currweap_cooldown;
	string weap1_cool;
	string weap2_cool;
	string weap3_cool;
	bool weapon1 = true;
	bool weapon2 = false;
	bool weapon3 = false;
private:
	//TextEntity* textObj[3];
};
