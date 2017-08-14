
#include "Stage1.h"
#include "GL\glew.h"
#include "Application.h"
#include "SceneManager.h"

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

}

void Stage1::Update(double dt)
{
	_elapsedTime += (float)dt;
	pressDelay += (float)dt;
	_dt = (float)dt;

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();


	//Mouse Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0) && pressDelay >= cooldownPressed)
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

		Vector3 currentPos;
		Application::GetCursorPos(&mouseX, &mouseY);
		currentPos.x = (float)mouseX / Application::GetWindowWidth() * m_worldWidth;;
		currentPos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;

		GameObject *tempObject = new  Projectile(GameObject::GO_PROJECTILE , this);
		tempObject->pos = theGhostProj->pos;
		tempObject->vel = tempObject->pos - currentPos;
		tempObject->scale.Set(3, 3, 3);
		tempObject->mass = 3;
		tempObject->active = true;
		theGhostProj->active = false;

		// add object into factory
		theFactory->createGameObject(tempObject);
	}

	//Update all Game Objects
	theFactory->updateGameObject();


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
