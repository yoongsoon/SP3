
#include "Stage1.h"
#include "GL\glew.h"
#include "Application.h"
#include "SceneManager.h"
#include "WeaponInfo.h"

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

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();


	//initialise the factory class
	// MUST BE FIRST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	theFactory = new Factory();

	theCollider = new CollisionManager(this);
	//intialise ghost projectile
	theGhostProj = new Projectile(Projectile::ARROW_PROJECTILE,GameObject::GO_PROJECTILE, this);
	// Initialize castle object
	theCastle = new Castle(GameObject::GO_BRICK, this);
	theFactory->createGameObject(theCastle);
	
	gom = new GameObjectManager(this);
	theplayer = new Player();
	theplayer->setScene(this);
	BackGround * theBackGround = new BackGround(BackGround::BACK_GROUND_STAGE1, GameObject::GO_BALL , this);
	theFactory->createGameObject(theBackGround);
}

void Stage1::Update(double dt)
{
	_elapsedTime += (float)dt;
	//pressDelay += (float)dt;
	_dt = (float)dt;

	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

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
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;

		Application::GetCursorPos(&mouseX, &mouseY);
		theGhostProj->pos.x = (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
		theGhostProj->pos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;
		theGhostProj->active = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		//when button click call discharge of weapon//TO DO****
		Vector3 currentPos;
		Application::GetCursorPos(&mouseX, &mouseY);
		currentPos.x = (float)mouseX / Application::GetWindowWidth() * m_worldWidth;;
		currentPos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;
	
		Weapon_Info potato;
		//potato.Get_OBJECT();
		
		GameObject *tempObject = new  Projectile(Projectile::ARROW_PROJECTILE, GameObject::GO_PROJECTILE , this);
		//info to shoot bullet
		potato.Discharge(currentPos, theGhostProj->pos,tempObject, this);
		tempObject->pos = theGhostProj->pos;

	/*	GameObject * tempObject = new  Projectile(Projectile::ARROW_PROJECTILE, GameObject::GO_PROJECTILE, this);
		tempObject->pos = theGhostProj->pos;
		tempObject->vel = tempObject->pos - currentPos;
		tempObject->scale.Set(3, 3, 3);
		tempObject->mass = 3;
		tempObject->active = true;*/


		theGhostProj->active = false;

		// add object into factory
		theFactory->createGameObject(tempObject);
	}


	if (Application::IsKeyPressed(VK_RIGHT) )
	{
		camera.position.x += _dt * 50;
		camera.target.x += _dt * 50;
	}

	if (Application::IsKeyPressed(VK_LEFT) )
	{
		camera.position.x -= _dt * 50;
		camera.target.x -= _dt * 50;
	}

	 //clamp camera position and target between World X coordinate 0 and m_world *2
	camera.position.x = Math::Clamp(camera.position.x, 0.f, m_worldWidth * 2);
	camera.target.x = Math::Clamp(camera.target.x, 0.f, m_worldWidth * 2);

	//Update all Game Objects
	theFactory->updateGameObject();
	// Update collisions
	theCollider->Update(dt);

	gom->update();
	theplayer->update();

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
}

void Stage1::Exit()
{
	SceneBase::Exit();
}

void Stage1::CreateEnemySoldier()
{
	GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_SOLDIER);
	theFactory->createGameObject(go);
	cout << "Soldier" << endl;
}

void Stage1::CreateEnemyArcher()
{
	GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_ARCHER);
	theFactory->createGameObject(go);
	cout << "Archer" << endl;
}

void Stage1::CreateEnemyWizard()
{
	GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_WIZARD);
	theFactory->createGameObject(go);
	cout << "Wizard" << endl;
}

void Stage1::CreateFriendlySoldier()
{
	GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_SOLDIER);
	theFactory->createGameObject(go);
	cout << "friend Soldier" << endl;
}

void Stage1::CreateFriendlyArcher()
{
	GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_ARCHER);
	theFactory->createGameObject(go);
	cout << "friend Archer" << endl;
}

void Stage1::CreateFriendlyWizard()
{
	GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_WIZARD);
	theFactory->createGameObject(go);
	cout << "friend Wizard" << endl;
}
