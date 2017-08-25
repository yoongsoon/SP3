#include "LoseScene.h"
#include "SceneManager.h"
#include "GL\glew.h"
#include "Application.h"

LoseScene * LoseScene::sInstance = new LoseScene(SceneManager::getInstance());

LoseScene::LoseScene(SceneManager * _scene)
{
	_scene->AddScene("LoseScene", this);
}

LoseScene::~LoseScene()
{

}

void LoseScene::Init()
{
	SceneBase::Init();
}

void LoseScene::Update(double dt)
{
	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	pressDelay += (float)dt;


	if (Application::IsKeyPressed(VK_RETURN) && pressDelay >= cooldownPressed)
	{
		if (sceneLost == RESTART_LOSE)
		{
			// restart the scene according to scene number
			// if scene number is 1 restart stage 1
			switch (stageNo)
			{
			case 1:
				SceneManager::getInstance()->SetActiveScene("Stage1");
				break;
			case 2:
				break;
			case 3:
				break;
			}
		}
		else if (sceneLost == MAIN_MENU_LOSE)
		{
			SceneManager::getInstance()->SetActiveScene("MainMenu");
		}
		else if (sceneLost == QUIT_LOSE)
		{
			exit(0);
		}
		


		pressDelay = 0.f;
	}


	if (Application::IsKeyPressed(VK_UP) && pressDelay >= cooldownPressed)
	{
		if (sceneLost == RESTART_LOSE)
		{
			sceneLost = QUIT_LOSE;
		}
		else if (sceneLost == QUIT_LOSE)
		{
			sceneLost = MAIN_MENU_LOSE;
		}
		else if (sceneLost == MAIN_MENU_LOSE)
		{
			sceneLost = RESTART_LOSE;
		}
		
		pressDelay = 0.f;
	}


	if (Application::IsKeyPressed(VK_DOWN) && pressDelay >= cooldownPressed)
	{
		if (sceneLost == RESTART_LOSE)
		{
			sceneLost = MAIN_MENU_LOSE;
		}
		else if (sceneLost == MAIN_MENU_LOSE)
		{
			sceneLost = QUIT_LOSE;
		}
		else if (sceneLost == QUIT_LOSE)
		{
			sceneLost = RESTART_LOSE;
		}

		
		pressDelay = 0.f;
	}

}

void LoseScene::Render()
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

	RenderMeshOnScreen(meshList[GEO_LOSE_SCENE], 80, 30, 160, 60);


	switch (sceneLost)
	{
	case RESTART_LOSE:
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 48, 38, 10, 10);
	}
	break;
	case MAIN_MENU_LOSE:
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 48, 24, 10, 10);
	}
	break;
	case QUIT_LOSE:
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 48, 10, 10, 10);
	}
	break;
	}
}

void LoseScene::Exit()
{
	SceneBase::Exit();
}
