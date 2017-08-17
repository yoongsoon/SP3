
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
	weap_manager = NULL;
	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//MiniMap
	theMiniMap = new MiniMap(GameObject::GO_NONE, this);


	//initialise the factory class
	// MUST BE FIRST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	theFactory = new Factory();

	theCollider = new CollisionManager(this);
	//intialise ghost projectile
	thePredictionLine = new GameObject*[10];
	for (size_t i = 0; i < 10; i++)
	{
		thePredictionLine[i]=new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	}
	thePredictGHOST = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	thePredictGHOST2 = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	theGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	theReleaseMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	theMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_PROJECTILE, this);
	//theFactory->createGameObject(theGhostProj);
	// Initialize castle object
	theCastle = new Castle(GameObject::GO_BRICK, this);
	theFactory->createGameObject(theCastle);

	theplayer = new Player();
	theplayer->setScene(this);
	gom = new GameObjectManager(this);
	BackGround * theBackGround = new BackGround(BackGround::BACK_GROUND_STAGE1, GameObject::GO_BALL, this);
	theFactory->createGameObject(theBackGround);

	AICastle * theAICastle = new AICastle(GameObject::GO_CASTLE, this);
	theFactory->createGameObject(theAICastle);

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

	thePlayer = new PlayerInfo();
	thePlayer->Init();
}

void Stage1::Update(double dt)
{
	_elapsedTime += (float)dt;
	//pressDelay += (float)dt;
	_dt = (float)dt;

	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

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
	//static bool spacepress = false;
	//if (Application::IsKeyPressed(VK_SPACE) && !spacepress)
	//{
	//	CreateEnemySoldier();
	//	spacepress = true;
	//}
	//else if (!Application::IsKeyPressed(VK_SPACE) && spacepress)
	//{
	//	spacepress = false;
	//}

	//Mouse Section

	//gets mouse position
	Vector3 currentPos;
	Application::GetCursorPos(&mouseX, &mouseY);
	currentPos.x = (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
	currentPos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;

		Application::GetCursorPos(&mouseX, &mouseY);
		//places current mouse pos and fixes to the pos where mouse clicked
		theGhostProj->pos = currentPos;// (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
	//	theGhostProj->pos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;
		theGhostProj->active = true;
		theReleaseMouseGhostProj->active = false;
		theFactory->createGameObject(theGhostProj);

	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		//when mouseclick release it renders wwhere the mouse was released 
		theReleaseMouseGhostProj->pos = currentPos;
		theReleaseMouseGhostProj->active = true;
		theFactory->createGameObject(theReleaseMouseGhostProj);

	
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
		theGhostProj->active = false;


	// add object into factory
	}
	//shows where mouse is(if need remove mouse cursor)
	theMouseGhostProj->pos = currentPos;
	//prediction line
	if (bLButtonState)
	{
		for (size_t i = 0; i < 10; i++)
		{
			double tline = i * 0.10;
			thePredictionLine[i]->pos.y = (((theGhostProj->pos.y) + ((theGhostProj->pos.y - theMouseGhostProj->pos.y) * tline)) + ((-9.8 *(tline * tline)) / 2));
			thePredictionLine[i]->pos.x = (theGhostProj->pos.x) + ((theGhostProj->pos.x - theMouseGhostProj->pos.x) * tline);
			thePredictionLine[i]->active = true;
			theFactory->createGameObject(thePredictionLine[i]);
		}
	}

	if (Application::IsKeyPressed(VK_RIGHT) )
	{
		//theMouseGhostProj->pos.x += _dt * 50;
		camera.position.x += _dt * 50;
		camera.target.x += _dt * 50;
	}

	if (Application::IsKeyPressed(VK_LEFT) )
	{
		//theMouseGhostProj->pos.x -= _dt * 50;
		camera.position.x -= _dt * 50;
		camera.target.x -= _dt * 50;
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
	theplayer->update();

	//potato->Update(dt);
	thePlayer->Update(dt);
	theFactory->createGameObject(theMouseGhostProj);

	//trying text for ui display
	/*std::ostringstream ss0;
	ss0.precision(5);
	ss0 << "NINJA X GTA";*/
	//textObj[0]->SetText(ss0.str());

	
}

void Stage1::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth , 0, m_worldHeight , -10, 10);
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
	
	//////Render background
	//RenderMeshOnScreen(meshList[SceneBase::GEO_BACKGROUND], 80, 30, 80, 60);

	//Render the all Game Objects
	theFactory->renderGameObject();

	theMiniMap->RenderUI();

	
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
