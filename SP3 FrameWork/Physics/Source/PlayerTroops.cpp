#include "PlayerTroops.h"
#include "SceneBase.h"
#include "Application.h"
#include "GL\glew.h"

PlayerTroop::PlayerTroop(GAMEOBJECT_TYPE GO_PLAYER, SceneBase * scene, PLAYER_TYPE meshvalue) :GameObject(GO_PLAYER, scene)
{
	playerMoveX = 0.f;
	if (meshvalue == P_SOLDIER)
	{
		float m_worldHeight = 100.f;
		float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
		//float zaxis = 1.f;
		active = true;
		meshValue = SceneBase::GEO_SOLDIER;
		scale.Set(10, 10, 1);
		vel.Set(10.f, 0.f, 0.f);
		pos.Set(0.f, m_worldHeight / 2, theScene->zaxis);
		playerType = PlayerTroop::P_SOLDIER;
		hp = 100.f;
		range = 1.f;
		damage = 10.f;
		attackcooldown = 3.f;
		cost = 50.f;
	}
	else if (meshvalue == P_ARCHER)
	{
		float m_worldHeight = 100.f;
		float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		active = true;
		meshValue = SceneBase::GEO_ARCHER;
		scale.Set(20, 15, 1);
		vel.Set(10.f, 0.f, 0.f);
		pos.Set(0.f, (m_worldHeight / 2) + 2, theScene->zaxis);
		playerType = PlayerTroop::P_ARCHER;
		hp = 50.f;
		range = 10.f;
		damage = 15.f;
		attackcooldown = 3.f;
		cost = 75.f;
	}
	else if (meshvalue == P_WIZARD)
	{
		float m_worldHeight = 100.f;
		float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		active = true;
		meshValue = SceneBase::GEO_WIZARD;
		scale.Set(10, 10, 10);
		vel.Set(10.f, 0.f, 0.f);
		pos.Set(0.f, m_worldHeight / 2, theScene->zaxis);
		playerType = PlayerTroop::P_WIZARD;
		hp = 70.f;
		range = 10.f;
		damage = 25.f;
		attackcooldown = 3.f;
		cost = 150.f;
	}
	StopToAttack = false;
	timer = 0.0f;
	Attacked = false;
}

PlayerTroop::~PlayerTroop()
{

}

void PlayerTroop::update()
{
	//destroy PlayerTroop when it ran out of hp
	float m_worldHeight = 100.f;
	float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	if (playerType == P_SOLDIER)
	{
		if (!StopToAttack)
		{
			pos += vel * theScene->_dt;
			meshValue = SceneBase::GEO_SOLDIER;
			//cout << pos.z << endl;
		}
		else
		{
			meshValue = SceneBase::GEO_SOLDIER_ATTACK;
		}
	}
	else if (playerType == P_ARCHER)
	{
		if (!StopToAttack)
		{
			pos += vel * theScene->_dt;
			meshValue = SceneBase::GEO_ARCHER;
		}
		else
		{
			meshValue = SceneBase::GEO_ARCHER_ATTACK;
		}
	}
	else if (playerType == P_WIZARD)
	{
		if (!StopToAttack)
		{
			pos += vel * theScene->_dt;
			meshValue = SceneBase::GEO_WIZARD;
		}
		else
		{
			meshValue = SceneBase::GEO_WIZARD_ATTACK;
		}
	}
		if (Attacked)
		{
			timer += theScene->_dt;
			if (timer > attackcooldown)
			{
				Attacked = false;
				timer = 0.0f;
				cout << "player RESET" << endl;
			}
		}
		if (hp <= 0.f)
		{
			active = false;
		}

	if (pos.x <= 0 || pos.x > (m_worldWidth * 3))
	{
		active = false;
	}

}

void PlayerTroop::render()
{
	//glDisable(GL_DEPTH_TEST);
	theScene->modelStack.PushMatrix();
	theScene->modelStack.Translate(pos.x, pos.y, pos.z);
	theScene->modelStack.Scale(scale.x, scale.y, scale.z);
	theScene->RenderMesh(theScene->meshList[meshValue], false);
	theScene->modelStack.PopMatrix();
	//glEnable(GL_DEPTH_TEST);
}