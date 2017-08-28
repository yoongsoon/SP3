#include "Score_Scene.h"
#include "GL\glew.h"
#include "Application.h"
#include "SceneManager.h"

Score_Scene * Score_Scene::sInstance = new Score_Scene(SceneManager::getInstance());

Score_Scene::Score_Scene(SceneManager * _scene)
{
	_scene->AddScene("ScoreScene", this);
}

Score_Scene::~Score_Scene()
{
}

void Score_Scene::Init()
{
	SceneBase::Init();
	theUIManager = new UIManager(this);
	sceneNumber = SceneBase::SC_SCORE;
	for (int i = 0; i < 5; ++i)
		m_highScore[i] = 0;
	
	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	if (Application::IsKeyPressed(VK_RETURN))
	{

		SceneManager::getInstance()->SetActiveScene("MainMenu");

	}
	theFile->setScene(this);
	theFile->loadScoreFromFile("Data.txt");
}

void Score_Scene::Update(double dt)
{
	_elapsedTime += (float)dt;
	pressDelay += (float)dt;

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	theUIManager->UpdateText();
}

void Score_Scene::Render()
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
	RenderMeshOnScreen(meshList[GEO_SCORESCENE], 80, 30, 160, 60);
	theUIManager->RenderText();
}

void Score_Scene::Exit()
{
	SceneBase::Exit();
}
