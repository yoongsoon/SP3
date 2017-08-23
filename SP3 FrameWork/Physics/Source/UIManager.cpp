#include "UIManager.h"
#include "SceneBase.h"
#include "Application.h"
#include "SceneManager.h"
#include "WeaponInfo.h"
#include <sstream>


UIManager::UIManager(SceneBase * scene)
	:theScene(scene)
{
}

UIManager::~UIManager()
{
}

void UIManager::UpdateText()
{
	a = theScene->thePlayer->GetWeapon();
	stringstream ss;
	ss << a;
	player_weap_choice = ss.str();
	//player_weap_choice = string(intstr);
	e = theScene->thePlayer->weap_manager[theScene->thePlayer->m_iCurrentWeapon]->Get_d_elapsedTime();
	stringstream ss1;
	ss1 << e;
	currweap_cooldown = ss1.str();

	e = theScene->thePlayer->weap_manager[0]->Get_d_elapsedTime();
	stringstream ss2;
	ss2 << e;
	weap1_cool = ss2.str();

	e = theScene->thePlayer->weap_manager[1]->Get_d_elapsedTime();
	stringstream ss3;
	ss3 << e;
	weap2_cool = ss3.str();

	e = theScene->thePlayer->weap_manager[2]->Get_d_elapsedTime();
	stringstream ss4;
	ss4 << e;
	weap3_cool = ss4.str();

	e = theScene->P_rotation;
	//e = theScene->
	stringstream ss5;
	ss5 << e;
	P_Rot = ss5.str();
}

void UIManager::Update()
{
	if (Application::IsKeyPressed(VK_BACK))
	{
		theScene->b_isPause = true;
	}

	if (theScene->b_isPause == true)
	{
		if (Application::IsKeyPressed(VK_UP) && theScene->pressDelay >= theScene->cooldownPressed)
		{
			if (theScene->menuPause == SceneBase::PAUSE_RESUME)
			{
				theScene->menuPause = SceneBase::PAUSE_MAINMENU;
			}
			else if (theScene->menuPause == SceneBase::PAUSE_MAINMENU)
			{
				theScene->menuPause = SceneBase::PAUSE_RESTART;
			}
			else
			{
				theScene->menuPause = SceneBase::PAUSE_RESUME;
			}
			theScene->pressDelay = 0.f;
		}

		if (Application::IsKeyPressed(VK_DOWN) && theScene->pressDelay >= theScene->cooldownPressed)
		{
			if (theScene->menuPause == SceneBase::PAUSE_RESUME)
			{
				theScene->menuPause = SceneBase::PAUSE_RESTART;
			}
			else if (theScene->menuPause == SceneBase::PAUSE_RESTART)
			{
				theScene->menuPause = SceneBase::PAUSE_MAINMENU;
			}
			else
			{
				theScene->menuPause = SceneBase::PAUSE_RESUME;
			}
			theScene->pressDelay = 0.f;
		}

		if (Application::IsKeyPressed(VK_RETURN) && theScene->pressDelay >= theScene->cooldownPressed)
		{
			if (theScene->menuPause == SceneBase::PAUSE_RESUME)
			{
				theScene->b_isPause = false;
			}
			else if (theScene->menuPause == SceneBase::PAUSE_RESTART)
			{
				theScene->Init();
				theScene->b_isPause = false;
				SceneManager::getInstance()->SetActiveScene("Stage1");
			}
			else if (theScene->menuPause == SceneBase::PAUSE_MAINMENU)
			{
				SceneManager::getInstance()->SetActiveScene("MainMenu");
			}
			theScene->pressDelay = 0.f;
		}
	}
}

void UIManager::Render()
{

	//----------------------------------------Mesh-------------------------------------------------------//
	theScene->modelStack.PushMatrix();
	theScene->modelStack.Translate(10.0f, 10.0f, 1.0f);
	theScene->modelStack.Scale(15.0f, 15.0f, 1.0f);

	if (theScene->weapon1)
	{
		theScene->RenderMesh(theScene->meshList[SceneBase::GEO_BOW_ARROW], false);
	}
	else if (theScene->weapon2)
	{
		theScene->RenderMesh(theScene->meshList[SceneBase::GEO_CANNON_BALLS], false);
	}
	else if (theScene->weapon3)
	{
		theScene->RenderMesh(theScene->meshList[SceneBase::GEO_CATAPULT_ROCKS], false);
	}
	theScene->modelStack.PopMatrix();

	//-------------------------------------Pause Menu---------------------------------------------------//

	//Render background
	if (theScene->b_isPause == true)
	{
		theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_PAUSE_MENU], 80, 30, 120, 40);

		switch (theScene->menuPause)
		{
		case SceneBase::PAUSE_RESUME:
			theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_PAUSE_ARROW], 60, 37, 10, 5);
			break;
		case SceneBase::PAUSE_RESTART:
			theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_PAUSE_ARROW], 60, 31, 10, 5);
			break;
		case SceneBase::PAUSE_MAINMENU:
			theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_PAUSE_ARROW], 60, 25, 10, 5);
			break;
		}
	}
}

void UIManager::RenderText()
{
	//--------------------------------------------------Text---------------------------------------------------------//
	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], player_weap_choice, Color(1, 0, 0), 5, 10, 20);
	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], currweap_cooldown, Color(1, 0, 0), 5, 10, 18);

	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], weap1_cool, Color(1, 0, 0), 5, 10, 15);
	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], weap2_cool, Color(1, 0, 0), 5, 10, 13);
	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], weap3_cool, Color(1, 0, 0), 5, 10, 11);
	//theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], P_Rotation, Color(1, 0, 0), 5, 10, 11);


	std::ostringstream ss;
	ss.precision(3);
	ss << theScene->theplayer->ReturnWallet();
	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 60, 55);

	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], "/", Color(0, 1, 0), 3, 69, 55);


	std::ostringstream ss1;
	ss1.precision(3);
	ss1 << theScene->theplayer->ReturnMaxWallet();
	theScene->RenderTextOnScreen(theScene->meshList[SceneBase::GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 72, 55);

}
