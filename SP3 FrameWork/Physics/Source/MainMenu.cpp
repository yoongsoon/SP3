#include "MainMenu.h"
#include "SceneManager.h"
#include "GL\glew.h"
#include "Application.h"

MainMenu * MainMenu::sInstance = new MainMenu(SceneManager::getInstance());

MainMenu::MainMenu(SceneManager * _scene)
{
	_scene->AddScene("MainMenu", this);
}

MainMenu::~MainMenu()
{
	
}

void MainMenu::Init()
{
	SceneBase::Init();
	for (int i = 0; i < 5; ++i)
	{
		m_highScore[i] = 0;
	}
	theFile->setScene(this);
	theFile->loadScoreFromFile("Data.txt");

}

void MainMenu::Update(double dt)
{
	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	pressDelay += (float)dt;


	if (Application::IsKeyPressed(VK_RETURN) && pressDelay >= cooldownPressed)
	{
		if (menuMain == START_MENU)
		{
			SceneManager::getInstance()->SetActiveScene("Stage1");
		}
		else if (menuMain == LOAD_MENU)
		{
			// load the level 
			theFile->loadLevel("Data.txt");

			// set the stage according to the level
			switch (theFile->currentStage)
			{
			case 1:
				SceneManager::getInstance()->SetActiveScene("Stage1");
				break;
			case 2:
				SceneManager::getInstance()->SetActiveScene("Stage2");
				break;
			case 3:
				break;
			}
		}
		else if (menuMain == HIGHSCORE_MENU)
		{
			SceneManager::getInstance()->SetActiveScene("ScoreScene");
		}
		else if (menuMain == QUIT_MENU)
		{
			exit(0);
		}

		pressDelay = 0.f;
	}


	if (Application::IsKeyPressed(VK_UP) && pressDelay >= cooldownPressed)
	{
		if (menuMain == START_MENU)
		{
			menuMain = QUIT_MENU;
		}
		else if (menuMain == QUIT_MENU)
		{
			menuMain = HIGHSCORE_MENU;
		}
		else if (menuMain == HIGHSCORE_MENU)
		{
			menuMain = LOAD_MENU;
		}
		else if (menuMain == LOAD_MENU)
		{
			menuMain = START_MENU;
		}

		pressDelay = 0.f;
	}


	if (Application::IsKeyPressed(VK_DOWN) && pressDelay >= cooldownPressed)
	{
		if (menuMain == START_MENU)
		{
			menuMain = LOAD_MENU;
		}
		else if (menuMain == LOAD_MENU)
		{
			menuMain = HIGHSCORE_MENU;
		}
		else if (menuMain == HIGHSCORE_MENU)
		{
			menuMain = QUIT_MENU;
		}
		else if (menuMain == QUIT_MENU)
		{
			menuMain = START_MENU;
		}

		pressDelay = 0.f;
	}

}

void MainMenu::Render()
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

	RenderMeshOnScreen(meshList[GEO_MAIN_MENU], 80, 30, 160, 60);


	switch (menuMain)
	{
	case START_MENU:
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 90, 40, 10, 10);
	}
	break;
	case LOAD_MENU:
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 90, 30, 10, 10);
	}
	break;
	case HIGHSCORE_MENU:
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 90, 20, 10, 10);
	}
	break;
	case QUIT_MENU:
	{
		RenderMeshOnScreen(meshList[SceneBase::GEO_PAUSE_ARROW], 90, 8, 10, 10);
	}
	break;
	}
}

void MainMenu::Exit()
{
	SceneBase::Exit();
}
