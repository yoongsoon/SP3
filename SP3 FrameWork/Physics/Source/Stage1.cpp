
#include "Stage1.h"
#include "GL\glew.h"
#include "Application.h"
#include "SceneManager.h"
#include "WeaponInfo.h"
#include "PlayerInfo.h"
#include "Cannon.h"
#include "Catapult.h"
#include "Bow.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

Stage1 * Stage1::sInstance = new Stage1(SceneManager::getInstance());

Stage1::Stage1(SceneManager * _scene)
{
	_scene->AddScene("Stage1", this);
}

Stage1::~Stage1()
{
}

void Stage1::Init()
{
	SceneBase::Init();
	m_sceneID = SceneBase::SC_01;
	m_wallStackCounter = 1;
	ghost_exist = false;
	release_ghost_exist = false;
	M_ghost_exist = false;
	canPredict = true;
	weap_manager = NULL;
	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Create Sound Engine to the play sounds
	CSoundEngine::getInstance()->Init();
	CSoundEngine::getInstance()->AddSound("BackGround Music", "Sound//Crossroads.ogg");
	CSoundEngine::getInstance()->PlayASound("BackGround Music", true, false);
	CSoundEngine::getInstance()->theCurrentSound->setVolume(0.4f);

	//MiniMap
	theMiniMap = new MiniMap(GameObject::GO_NONE, this);

	//initialise the factory class
	// MUST BE FIRST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	theFactory = new Factory();

	theCollider = new CollisionManager(this);
	//intialise ghost projectile prediction
	thePredictionLine = new GameObject*[10];
	for (size_t i = 0; i < 10; i++)
	{
		thePredictionLine[i] = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
		theFactory->createGameObject(thePredictionLine[i]);
	}
	//initialize ghosts
	theGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	theFactory->createGameObject(theGhostProj);

	theReleaseMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	theFactory->createGameObject(theReleaseMouseGhostProj);

	theMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	theMouseGhostProj->active = true;
	theFactory->createGameObject(theMouseGhostProj);

	Castle * theCastle = new Castle(GameObject::GO_CASTLE, this, 0);
	theFactory->createGameObject(theCastle);

	// Initialize castle object
	for (m_wallStackCounter; m_wallStackCounter <= 6; ++m_wallStackCounter)
	{
		Castle * theWall = new Castle(GameObject::GO_BRICK, this, m_wallStackCounter);
		theFactory->createGameObject(theWall);
	}

	AICastle * theAICastle = new AICastle(GameObject::GO_AI_CASTLE, this);
	theAICastle->m_hp = 500.f;
	theFactory->createGameObject(theAICastle);

	BackGround * theBackGround = new BackGround(BackGround::BACK_GROUND_STAGE1, GameObject::GO_NONE, this);
	theFactory->createGameObject(theBackGround);

	theplayer = new Player();
	theplayer->setScene(this);
	gom = new GameObjectManager(this);

	scenebase = new SceneBase();
	//CHANGE THIS TO Bow/Cannon/Catapult for different cooldown
	//weap_manager = new Weapon_Info*[3];
	/*potato = new Bow();
	potato->Init();*/
	//weap_manager[0] = new Bow();
	//weap_manager[0]->Init();
	//weap_manager[1] = new Cannon();
	//weap_manager[1]->Init();
	//weap_manager[2] = new Catapult();
	//weap_manager[2]->Init();
	//player itself
	thePlayer = new PlayerInfo();
	thePlayer->Init();

	SpriteAnimation* wizard = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD]);
	SpriteAnimation* archer = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER]);
	SpriteAnimation* soldier = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER]);
	if (wizard)
	{
		wizard->m_anim = new Animation();
		wizard->m_anim->Set(0, 15, 0, 1.0f, true);
	}
	if (archer)
	{
		archer->m_anim = new Animation();
		archer->m_anim->Set(0, 15, 0, 1.0f, true);
	}
	if (soldier)
	{
		soldier->m_anim = new Animation();
		soldier->m_anim->Set(0, 15, 0, 1.0f, true);
	}
}

void Stage1::Update(double dt)
{
	_elapsedTime += (float)dt;
	pressDelay += (float)dt;
	_dt = (float)dt;

	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	if (Application::IsKeyPressed(VK_BACK))
	{
		b_isPause = true;
	}



	if (b_isPause == false)
	{
		static bool bow = false;
		if (Application::IsKeyPressed(VK_NUMPAD1) && !bow)
		{
			//curr_weapon = 0;
			thePlayer->SetWeapon(0);
			bow = true;
		}
		else if (!Application::IsKeyPressed(VK_NUMPAD1) && bow)
		{
			bow = false;
		}
		//	static bool bow = false;
		if (Application::IsKeyPressed(VK_NUMPAD2) && !bow)
		{
			//curr_weapon = 1;
			thePlayer->SetWeapon(1);
			bow = true;
		}
		else if (!Application::IsKeyPressed(VK_NUMPAD2) && bow)
		{
			bow = false;
		}
		//	static bool bow = false;
		if (Application::IsKeyPressed(VK_NUMPAD3) && !bow)
		{
			//curr_weapon = 2;
			thePlayer->SetWeapon(2);
			bow = true;
		}
		else if (!Application::IsKeyPressed(VK_NUMPAD3) && bow)
		{
			bow = false;
		}
		static bool onepress = false;
		if (Application::IsKeyPressed('1') && !onepress)
		{
			CreateEnemySoldier();
			onepress = true;
		}
		else if (!Application::IsKeyPressed('1') && onepress)
		{
			onepress = false;
		}

		static bool twopress = false;
		if (Application::IsKeyPressed('2') && !twopress)
		{
			CreateEnemyArcher();
			twopress = true;
		}
		else if (!Application::IsKeyPressed('2') && twopress)
		{
			twopress = false;
		}
		static bool threepress = false;
		if (Application::IsKeyPressed('3') && !threepress)
		{
			CreateEnemyWizard();
			threepress = true;
		}
		else if (!Application::IsKeyPressed('3') && threepress)
		{
			threepress = false;
		}

		static bool fourpress = false;
		if (Application::IsKeyPressed('4') && !fourpress)
		{
			CreateFriendlySoldier();
			fourpress = true;
		}
		else if (!Application::IsKeyPressed('4') && fourpress)
		{
			fourpress = false;
		}

		static bool fivepress = false;
		if (Application::IsKeyPressed('5') && !fivepress)
		{
			CreateFriendlyArcher();
			fivepress = true;
		}
		else if (!Application::IsKeyPressed('5') && fivepress)
		{
			fivepress = false;
		}
		static bool sixpress = false;
		if (Application::IsKeyPressed('6') && !sixpress)
		{
			CreateFriendlyWizard();
			sixpress = true;
		}
		else if (!Application::IsKeyPressed('6') && sixpress)
		{
			sixpress = false;
		}

		//Mouse Section
		Vector3 currentPos;
		Application::GetCursorPos(&mouseX, &mouseY);
		currentPos.x = (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
		currentPos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;

		static bool bLButtonState = false;
		//to only create ghosts balls ONCE not every update
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;

			Application::GetCursorPos(&mouseX, &mouseY);
			//places current mouse pos and fixes to the pos where mouse clicked
			theGhostProj->pos = currentPos;// (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
										   //	theGhostProj->pos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;
			theGhostProj->active = true;
			//changes prev mouse ghost
			theReleaseMouseGhostProj->active = false;


		}
		else if (bLButtonState && !Application::IsMousePressed(0))
		{
			bLButtonState = false;
			//when mouseclick release it renders wwhere the mouse was released 
			theReleaseMouseGhostProj->pos = currentPos;
			theReleaseMouseGhostProj->active = true;

			//shoots projectile
			thePlayer->DischargePPTEST(theGhostProj->pos, currentPos, this);

			//Weapon_Info potato;
			//potato.Get_OBJECT();


			//info to shoot bullet
			//potato->Discharge(theGhostProj->pos, currentPos, this);
			//GameObject *tempObject = new  Projectile(Projectile::ARROW_PROJECTILE, GameObject::GO_PROJECTILE , this);
			//GameObject *tempObject1 = new  Projectile(Projectile::CANNON_BALL_PROJECTILE, GameObject::GO_PROJECTILE, this);
			//GameObject *tempObject2 = new  Projectile(Projectile::ROCK_PROJECTILE, GameObject::GO_PROJECTILE, this);
			////info to shoot bullet
			//tempObject->pos = theGhostProj->pos;
			//tempObject1->pos = theGhostProj->pos;
			//tempObject2->pos = theGhostProj->pos;
			//weap_manager[0]->Discharge(currentPos, theGhostProj->pos,tempObject, this);
			//thePlayer->DischargePPTEST(currentPos, theGhostProj->pos, tempObject, this);
			//weap_manager[1]->Discharge(currentPos, theGhostProj->pos, tempObject1, this);
			//thePlayer->DischargePPTEST(currentPos, theGhostProj->pos, tempObject, this);
			//weap_manager[2]->Discharge(currentPos, theGhostProj->pos, tempObject2, this);
			//theFactory->createGameObject(tempObject);
			//theFactory->createGameObject(tempObject1);
			//theFactory->createGameObject(tempObject2);
			//canPredict = true;
			theGhostProj->active = false;
			// add object into factory
		}
		//shows where mouse is(if need remove mouse cursor)
		theMouseGhostProj->pos = currentPos;
		//prediction line when hold leftclick
		if (bLButtonState)
		{
			for (size_t i = 0; i < 10; i++)
			{
				double tline = i * 0.10;
				thePredictionLine[i]->pos.y = (((theGhostProj->pos.y) + ((theGhostProj->pos.y - theMouseGhostProj->pos.y) * tline)) + ((-9.8 *(tline * tline)) / 2));
				thePredictionLine[i]->pos.x = (theGhostProj->pos.x) + ((theGhostProj->pos.x - theMouseGhostProj->pos.x) * tline);
				thePredictionLine[i]->active = true;
			}
			//canPredict = false;
		}

		// scrolling right
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			//theMouseGhostProj->pos.x += _dt * 50;
			camera.position.x += _dt * 80;
			camera.target.x += _dt * 80;
		}
		// scrolling left
		if (Application::IsKeyPressed(VK_LEFT))
		{
			//theMouseGhostProj->pos.x -= _dt * 50;
			camera.position.x -= _dt * 80;
			camera.target.x -= _dt * 80;
		}
		theMouseGhostProj->active = true;

		//clamp camera position and target between World X coordinate 0 and m_world *2
		camera.position.x = Math::Clamp(camera.position.x, 0.f, m_worldWidth * 2);
		camera.target.x = Math::Clamp(camera.target.x, 0.f, m_worldWidth * 2);

		//Update all Game Objects
		theFactory->updateGameObject();

		// Update collisions
		theCollider->Update(dt);

		gom->update();
		//player units
		theplayer->update();
		//playerinfo
		thePlayer->Update(dt);

		theMiniMap->Update();

		SpriteAnimation* wizard = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD]);
		SpriteAnimation* archer = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER]);
		SpriteAnimation* soldier = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER]);
		if (wizard)
		{
			wizard->Update(dt);
			wizard->m_anim->animActive = true;
		}
		if (archer)
		{
			archer->Update(dt);
			archer->m_anim->animActive = true;
		}
		if (soldier)
		{
			soldier->Update(dt);
			soldier->m_anim->animActive = true;
		}
	}
	else
	{
		if (Application::IsKeyPressed(VK_UP) && pressDelay >= cooldownPressed)
		{
			if (menuPause == PAUSE_RESUME)
			{
				menuPause = PAUSE_MAINMENU;
			}
			else if (menuPause == PAUSE_MAINMENU)
			{
				menuPause = PAUSE_RESTART;
			}
			else
			{
				menuPause = PAUSE_RESUME;
			}
			pressDelay = 0.f;
		}

		if (Application::IsKeyPressed(VK_DOWN) && pressDelay >= cooldownPressed)
		{
			if (menuPause == PAUSE_RESUME)
			{
				menuPause = PAUSE_RESTART;
			}
			else if (menuPause == PAUSE_RESTART)
			{
				menuPause = PAUSE_MAINMENU;
			}
			else
			{
				menuPause = PAUSE_RESUME;
			}
			pressDelay = 0.f;
		}

		if (Application::IsKeyPressed(VK_RETURN) && pressDelay >= cooldownPressed)
		{
			if (menuPause == PAUSE_RESUME)
			{
				b_isPause = false;
			}
			else if (menuPause == PAUSE_RESTART)
			{
				Stage1::Init();
				b_isPause = false;
				SceneManager::getInstance()->SetActiveScene("Stage1");
			}
			else if (menuPause == PAUSE_MAINMENU)
			{
				
			}
			pressDelay = 0.f;
		}
	}



	/*TEXT STUFF*/
	//std::ostringstream ss0;
	//ss0.precision(5);
	//ss0 << "NINJA X GTA";
	//textObj[0]->SetText(ss0.str());

	a = thePlayer->GetWeapon();
	stringstream ss;
	ss << a;
	player_weap_choice = ss.str();
	//player_weap_choice = string(intstr);
	e = thePlayer->weap_manager[thePlayer->m_iCurrentWeapon]->Get_d_elapsedTime();
	stringstream ss1;
	ss1 << e;
	currweap_cooldown = ss1.str();

	e = thePlayer->weap_manager[0]->Get_d_elapsedTime();
	stringstream ss2;
	ss2 << e;
	weap1_cool = ss2.str();
	e = thePlayer->weap_manager[1]->Get_d_elapsedTime();
	stringstream ss3;
	ss3 << e;
	weap2_cool = ss3.str();
	e = thePlayer->weap_manager[2]->Get_d_elapsedTime();
	stringstream ss4;
	ss4 << e;
	weap3_cool = ss4.str();
}

void Stage1::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();


	//Render the all Game Objects
	theFactory->renderGameObject();

	theMiniMap->RenderUI();

	//Render background
	if (b_isPause == true)
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_MENU], 80, 30, 120, 40);

		switch (menuPause)
		{
		case PAUSE_RESUME:
			RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 60, 37, 10, 5);
			break;
		case PAUSE_RESTART:
			RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 60, 31, 10, 5);
			break;
		case PAUSE_MAINMENU:
			RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 60, 25, 10, 5);
			break;
		}
	}


	//modelStack.PushMatrix();
	//modelStack.Translate(100.f, 25.f, 2.f);
	//modelStack.Scale(100.f, 50.f, 1.f);
	//RenderMesh(meshList[GEO_TERRAIN], false);
	//modelStack.PopMatrix();


	//render choice of weapon
	RenderTextOnScreen(meshList[GEO_TEXT], player_weap_choice, Color(1, 0, 0), 5, 10, 20);
	RenderTextOnScreen(meshList[GEO_TEXT], currweap_cooldown, Color(1, 0, 0), 5, 10, 18);

	RenderTextOnScreen(meshList[GEO_TEXT], weap1_cool, Color(1, 0, 0), 5, 10, 15);
	RenderTextOnScreen(meshList[GEO_TEXT], weap2_cool, Color(1, 0, 0), 5, 10, 13);
	RenderTextOnScreen(meshList[GEO_TEXT], weap3_cool, Color(1, 0, 0), 5, 10, 11);
}

void Stage1::Exit()
{
	SceneBase::Exit();
}

void Stage1::CreateEnemySoldier()
{
	GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_SOLDIER);
	Enemy * tempEnemy = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_SOLDIER);
	cout << theplayer->ReturnEnemyWallet() << endl;
	if (theplayer->ReturnEnemyWallet() > tempEnemy->cost)
	{
		theplayer->ReduceEnemyWalletAmount(tempEnemy->cost);
		theFactory->createGameObject(go);
		cout << "Soldier" << endl;
	}
	delete tempEnemy;
}

void Stage1::CreateEnemyArcher()
{
	GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_ARCHER);
	Enemy * tempEnemy = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_ARCHER);
	cout << theplayer->ReturnEnemyWallet() << endl;
	if (theplayer->ReturnEnemyWallet() > tempEnemy->cost)
	{
		theplayer->ReduceEnemyWalletAmount(tempEnemy->cost);
		theFactory->createGameObject(go);
		cout << "Archer" << endl;
	}
}

void Stage1::CreateEnemyWizard()
{
	GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_WIZARD);
	Enemy * tempEnemy = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_WIZARD);
	cout << theplayer->ReturnEnemyWallet() << endl;
	if (theplayer->ReturnEnemyWallet() > tempEnemy->cost)
	{
		theplayer->ReduceEnemyWalletAmount(tempEnemy->cost);
		theFactory->createGameObject(go);
		cout << "Wizard" << endl;
	}
}

void Stage1::CreateFriendlySoldier()
{
	GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_SOLDIER);
	PlayerTroop * tempPlayer = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_SOLDIER);
	cout << theplayer->ReturnWallet() << endl;
	if (theplayer->ReturnWallet() > tempPlayer->cost)
	{
		theplayer->ReduceWalletAmount(tempPlayer->cost);
		theFactory->createGameObject(go);
		cout << "friend Soldier" << endl;
	}
}

void Stage1::CreateFriendlyArcher()
{
	GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_ARCHER);
	PlayerTroop * tempPlayer = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_ARCHER);
	cout << theplayer->ReturnWallet() << endl;
	if (theplayer->ReturnWallet() > tempPlayer->cost)
	{
		theplayer->ReduceWalletAmount(tempPlayer->cost);
		theFactory->createGameObject(go);
		cout << "friend Archer" << endl;
	}
}

void Stage1::CreateFriendlyWizard()
{
	GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_WIZARD);
	PlayerTroop * tempPlayer = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_WIZARD);
	cout << theplayer->ReturnWallet() << endl;
	if (theplayer->ReturnWallet() > tempPlayer->cost)
	{
		theplayer->ReduceWalletAmount(tempPlayer->cost);
		theFactory->createGameObject(go);
		cout << "friend Wizard" << endl;
	}
}
