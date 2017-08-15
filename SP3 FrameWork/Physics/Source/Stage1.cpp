
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

	//intialise ghost projectile
	theGhostProj = new Projectile(GameObject::GO_PROJECTILE, this);
	//initialise the factory class
	theFactory = new Factory();

	theEnemy = new Enemy(GameObject::GO_ENEMY, this);
	gom = new GameObjectManager(this);

	GameObject *go = new Enemy(GameObject::GO_ENEMY, this);
	go->active = true;
	go->meshValue = SceneBase::GEO_ARCHER;
	go->scale.Set(5, 5, 5);
	go->vel.Set(0.f, 0.f, 0.f);
	go->pos.Set(m_worldWidth / 10, m_worldHeight / 2, 0.f);
	static_cast<Enemy*> (go)->enemyType = Enemy::E_ARCHER;
	static_cast<Enemy*> (go)->hp = 100.f;
	static_cast<Enemy*> (go)->range = 1.f;
	static_cast<Enemy*> (go)->damage = 10.f;
	static_cast<Enemy*> (go)->cooldown = 3.f;
	theFactory->createGameObject(go);
}

void Stage1::Update(double dt)
{
	_elapsedTime += (float)dt;
	//pressDelay += (float)dt;
	_dt = (float)dt;

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	static bool spacepress = false;
	if (Application::IsKeyPressed(VK_SPACE) && !spacepress)
	{
		GameObject *go = new Enemy(GameObject::GO_ENEMY, this);
		go->active = true;
		go->scale.Set(5, 5, 5);
		go->vel.Set(-10.f, 0.f, 0.f);
		go->pos.Set(m_worldWidth / 2, m_worldHeight / 2, 0.f);
		static_cast<Enemy*> (go)->enemyType = Enemy::E_SOLDIER;
		static_cast<Enemy*> (go)->hp = 100.f;
		static_cast<Enemy*> (go)->range = 1.f;
		static_cast<Enemy*> (go)->damage = 10.f;
		static_cast<Enemy*> (go)->cooldown = 3.f;
		theFactory->createGameObject(go);
		/*cout << "hi" << endl;*/
		spacepress = true;
	}
	else if (!Application::IsKeyPressed(VK_SPACE) && spacepress)
	{
		spacepress = false;
	}

	//Mouse Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;

		Application::GetCursorPos(&mouseX, &mouseY);
		theGhostProj->pos.x = (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
		theGhostProj->pos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;
		theGhostProj->active = true;
		pressDelay = 0.f;
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
		
		GameObject *tempObject = new  Projectile(GameObject::GO_PROJECTILE , this);
		//info to shoot bullet
		potato.Discharge(currentPos, theGhostProj->pos,tempObject, this);
	/*	tempObject->pos = theGhostProj->pos;
		tempObject->vel = tempObject->pos - currentPos;
		tempObject->scale.Set(3, 3, 3);
		tempObject->mass = 3;
		tempObject->active = true;
*/

		theGhostProj->active = false;

		// add object into factory
		theFactory->createGameObject(tempObject);
	}
	//Update all Game Objects
	theFactory->updateGameObject();
	gom->update();
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
	
	//Render background
	RenderMeshOnScreen(meshList[SceneBase::GEO_BACKGROUND], 40, 30, 80, 60);

	//Render the all Game Objects
	theFactory->renderGameObject();
}

void Stage1::Exit()
{
	SceneBase::Exit();
}
