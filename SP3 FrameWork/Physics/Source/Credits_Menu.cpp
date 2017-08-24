#include "Credits_Menu.h"
#include "SceneManager.h"
#include "GL\glew.h"
#include "Application.h"

Credits_Menu * Credits_Menu::sInstance = new Credits_Menu(SceneManager::getInstance());

Credits_Menu::Credits_Menu(SceneManager * _scene)
{
	_scene->AddScene("Credits", this);
}

Credits_Menu::~Credits_Menu()
{

}

void Credits_Menu::Init()
{
	SceneBase::Init();
}

void Credits_Menu::Update(double dt)
{
	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	pressDelay += (float)dt;


	if (Application::IsKeyPressed(VK_RETURN))
	{
	
			SceneManager::getInstance()->SetActiveScene("MainMenu");
		
	}
}

void Credits_Menu::Render()
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

	RenderMeshOnScreen(meshList[GEO_CREDITS], 80, 30, 160, 60);


	
}

void Credits_Menu::Exit()
{
	SceneBase::Exit();
}
