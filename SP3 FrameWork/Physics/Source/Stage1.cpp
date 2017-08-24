
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
	P_rotation = 1.f;
	//Physics code here
	m_speed = 1.f;
	m_levelScore = 10000;

	Math::InitRNG();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Create Sound Engine to the play sounds
	CSoundEngine::getInstance()->Init();
	CSoundEngine::getInstance()->AddSound("BackGround Music", "Sound//Crossroads.ogg");
	CSoundEngine::getInstance()->PlayASound("BackGround Music", true, false);
	CSoundEngine::getInstance()->theCurrentSound->setVolume(0.4f);


	//initialise the factory class
	// MUST BE FIRST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	theFactory = new Factory();

	//MiniMap
	theMiniMap = new MiniMap(GameObject::GO_MINI_MAP, this);

	theCollider = new CollisionManager(this);
	//intialise ghost projectile prediction
	thePredictionLine = new GameObject*[10];
	for (size_t i = 0; i < 10; i++)
	{
		thePredictionLine[i] = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
		theFactory->createGameObject(thePredictionLine[i]);
	}
	//initialize ghosts
	theGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
	theFactory->createGameObject(theGhostProj);

	theReleaseMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
	theFactory->createGameObject(theReleaseMouseGhostProj);

	theMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
	theMouseGhostProj->active = true;
	theFactory->createGameObject(theMouseGhostProj);

	// BUILDINGS
	for (m_wallStackCounter; m_wallStackCounter <= 6; ++m_wallStackCounter)
	{
		Buildings * theWall = new Buildings(GameObject::GO_P_BRICK, this, m_wallStackCounter);
		theFactory->createGameObject(theWall);
	}
	Buildings * theCastle = new Buildings(GameObject::GO_P_CASTLE, this, 0);
	theFactory->createGameObject(theCastle);
	
	for (m_wallStackCounter; m_wallStackCounter <= 6; ++m_wallStackCounter)
	{
		Buildings * theWall = new Buildings(GameObject::GO_AI_BRICK, this, m_wallStackCounter);
		theFactory->createGameObject(theWall);
	}
	AICastle * theAICastle = new AICastle(GameObject::GO_AI_CASTLE, this);
	theFactory->createGameObject(theAICastle);

	BackGround * theBackGround = new BackGround(BackGround::BACK_GROUND_STAGE1, GameObject::GO_NONE, this);
	theFactory->createGameObject(theBackGround);

	theplayer = new Player();
	theplayer->setScene(this);
	gom = new GameObjectManager(this);

	/*scenebase = new SceneBase();*/
	
	//player itself
	thePlayer = new PlayerInfo();
	thePlayer->Init();

	SpriteAnimation* wizard = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD]);
	SpriteAnimation* wizardattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD_ATTACK]);
	SpriteAnimation* archer = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER]);
	SpriteAnimation* archerattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER_ATTACK]);
	SpriteAnimation* soldier = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER]);
	SpriteAnimation* soldierattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER_ATTACK]);
	//SpriteAnimation* P_weapon_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_BOW_ARROW]);
	SpriteAnimation* P_Bow_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_BOW_ARROW]);
//	SpriteAnimation* P_Cannon_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_CANNON_BALLS]);
	SpriteAnimation* P_Catapult_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_CATAPULT_ROCKS]);

	if (wizard)
	{
		wizard->m_anim = new Animation();
		wizard->m_anim->Set(0, 5, 0, 1.0f, true);
	}
	if (wizardattack)
	{
		wizardattack->m_anim = new Animation();
		wizardattack->m_anim->Set(0, 8, 0, 1.0f, true);
	}
	if (archer)
	{
		archer->m_anim = new Animation();
		archer->m_anim->Set(0, 3, 0, 1.0f, true);
	}
	if (archerattack)
	{
		archerattack->m_anim = new Animation();
		archerattack->m_anim->Set(0, 2, 0, 1.0f, true);
	}
	if (soldier)
	{
		soldier->m_anim = new Animation();
		soldier->m_anim->Set(0, 5, 0, 1.0f, true);
	}
	if (soldierattack)
	{
		soldierattack->m_anim = new Animation();
		soldierattack->m_anim->Set(0, 4, 0, 1.0f, true);
	}
	//if (P_weapon_Sprite)
	if (P_Bow_Sprite)

	{
		P_Bow_Sprite->m_anim = new Animation();
		P_Bow_Sprite->m_anim->Set(0, 12, 0, 1.0f, true);
	}
//	if (P_Cannon_Sprite)
//	{
//		P_Cannon_Sprite->m_anim = new Animation();
//		P_Cannon_Sprite->m_anim->Set(0, 15, 0, 1.0f, true);
//	}
	if (P_Catapult_Sprite)
	{
		P_Catapult_Sprite->m_anim = new Animation();
		P_Catapult_Sprite->m_anim->Set(0, 10, 0, 1.0f, true);
	}

	theUIManager = new UIManager(this);

	 theFile = new FileConfiguration(this);
}

void Stage1::Update(double dt)
{
	_elapsedTime += (float)dt;
	pressDelay += (float)dt;
	_dt = (float)dt;

	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	if (Application::IsKeyPressed('K') && pressDelay >= cooldownPressed)
	{
		theFile->saveFile("Data.txt");
		pressDelay = 0.f;
	}
	if (Application::IsKeyPressed('L') && pressDelay >= cooldownPressed)
	{
		theFile->loadFile("Data.txt");
		pressDelay = 0.f;
	}



	if (b_isPause == false)
	{
		static bool bow = false;
		if (Application::IsKeyPressed(VK_NUMPAD1) && !bow)
		{
			//curr_weapon = 0;
			thePlayer->SetWeapon(0);
			bow = true;

			weapon1 = true;

			weapon2 = false;
			weapon3 = false;
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

			weapon2 = true;

			weapon1 = false;
			weapon3 = false;
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

			weapon3 = true;

			weapon1 = false;
			weapon2 = false;
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
			//theGhostProj->active = false;
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
				thePredictionLine[i]->pos.y = (((50) + ((theGhostProj->pos.y - theMouseGhostProj->pos.y) * tline)) + ((-9.8 *(tline * tline)) / 2));
				thePredictionLine[i]->pos.x = (20) + ((theGhostProj->pos.x - theMouseGhostProj->pos.x) * tline);
				thePredictionLine[i]->pos.z = 5.0f;
				thePredictionLine[i]->active = true;
			}
			//canPredict = false;
			P_rotation = Math::RadianToDegree(atan2f(theGhostProj->pos.y - theMouseGhostProj->pos.y, theGhostProj->pos.x - theMouseGhostProj->pos.x));

		}
		else
		{
			P_rotation = 1;
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
		theMouseGhostProj->active = false;

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
		SpriteAnimation* wizardattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD_ATTACK]);
		SpriteAnimation* archer = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER]);
		SpriteAnimation* archerattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER_ATTACK]);
		SpriteAnimation* soldier = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER]);
		SpriteAnimation* soldierattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER_ATTACK]);
		//SpriteAnimation* P_weapon_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_BOW_ARROW]);
		SpriteAnimation* P_Bow_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_BOW_ARROW]);
		//SpriteAnimation* P_Cannon_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_CANNON_BALLS]);
		SpriteAnimation* P_Catapult_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_CATAPULT_ROCKS]);

		if (wizard)
		{
			wizard->Update(dt);
			wizard->m_anim->animActive = true;
		}
		if (wizardattack)
		{
			wizardattack->Update(dt);
			wizardattack->m_anim->animActive = true;
		}
		if (archer)
		{
			archer->Update(dt);
			archer->m_anim->animActive = true;
		}
		if (archerattack)
		{
			archerattack->Update(dt);
			archerattack->m_anim->animActive = true;
		}
		if (soldier)
		{
			soldier->Update(dt);
			soldier->m_anim->animActive = true;
		}
		if (soldierattack)
		{
			soldierattack->Update(dt);
			soldierattack->m_anim->animActive = true;
		}
		//if (P_weapon_Sprite)
		if (P_Bow_Sprite)
		{
			P_Bow_Sprite->Update(dt);
			P_Bow_Sprite->m_anim->animActive = true;
		}
	//	if (P_Cannon_Sprite)
	//	{
	//		P_Cannon_Sprite->Update(dt);
	//		P_Cannon_Sprite->m_anim->animActive = true;
	//	}
		if (P_Catapult_Sprite)
		{
			P_Catapult_Sprite->Update(dt);
			P_Catapult_Sprite->m_anim->animActive = true;
		}
	}
	
	//P_rotation = Math::RadianToDegree(atan2f(theGhostProj->pos.y - theReleaseMouseGhostProj->pos.y, theGhostProj->pos.x - theReleaseMouseGhostProj->pos.x));

	theUIManager->Update();
	theUIManager->UpdateText();

	/*TEXT STUFF*/
	//std::ostringstream ss0;
	//ss0.precision(5);
	//ss0 << "NINJA X GTA";
	//textObj[0]->SetText(ss0.str());

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

	
	//modelStack.PushMatrix();
	//modelStack.Translate(100.f, 25.f, 2.f);
	//modelStack.Scale(100.f, 50.f, 1.f);
	//RenderMesh(meshList[GEO_TERRAIN], false);
	//modelStack.PopMatrix();


	theUIManager->Render();
	theUIManager->RenderText();

	//RenderMeshOnScreen(meshList[GEO_P_CANNON], 30.0f, 80.0f, 15.0f, 15.0f);

	//rendering problem
	modelStack.PushMatrix();
	modelStack.Translate(30.0f, 40.0f, 5.0f);
	//modelStack.Rotate(P_rotation, 0, 0, 1);
	modelStack.Scale(15.0f, 15.0f, 1.0f);
	//RenderMesh(meshList[GEO_P_CANNON], false);
	RenderMesh(meshList[GEO_P_CANNON_STAND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20.0f, 40.0f, 4.0f);
	modelStack.Rotate(P_rotation, 0, 0, 1);
	modelStack.Scale(15.0f, 15.0f, 1.0f);
	RenderMesh(meshList[GEO_P_CANNON], false);
	//RenderMesh(meshList[GEO_P_CANNON_STAND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20.0f, 30.0f, 5.0f);
	//modelStack.Rotate(P_rotation, 0, 0, 1);
	modelStack.Scale(15.0f, 15.0f, 1.0f);
	RenderMesh(meshList[GEO_P_CATAPULT_ROCKS], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(20.0f, 50.0f, 5.0f);
	modelStack.Rotate(P_rotation, 0, 0, 1);
	modelStack.Scale(15.0f, 15.0f, 1.0f);
	RenderMesh(meshList[GEO_P_BOW_ARROW], false);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Translate(20.0f, 40.0f, 1.0f);
	modelStack.Scale(15.0f, 15.0f, 1.0f);
	RenderMesh(meshList[GEO_P_BOW_ARROW], false);
	modelStack.PopMatrix();*/
	
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
		zaxis++;
		cout << zaxis << endl;
		cout << "whee" << endl;
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
		zaxis++;
		cout << zaxis << endl;
		cout << "whee" << endl;
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
