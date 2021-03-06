#include "Enemy.h"
#include "SceneBase.h"
#include "Application.h"
#include "GL\glew.h"
#include "FileConfiguration.h"

Enemy::Enemy(GAMEOBJECT_TYPE GO_ENEMY, SceneBase * scene, ENEMY_TYPE meshvalue) :GameObject(GO_ENEMY, scene)
{
	enemyMoveX = 0.f;
	if (meshvalue == E_SOLDIER)
	{
		float m_worldHeight = 100.f;
		float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		active = true;
		meshValue = SceneBase::GEO_ENEMY_SOLDIER;
		scale.Set(10, 10, 1.f);
		vel.Set(-30.f, 0.f, 0.f);
		if (FileConfiguration::b_isLoadLevel == false)
		{
			pos.Set(theScene->theAICastle->pos.x, theScene->theAICastle->pos.y - (theScene->theAICastle->scale.y / 3) + theScene->enemy_yaxis, theScene->zaxis);
		}
		enemyType = Enemy::E_SOLDIER;
		hp = 100.f;
		range = 1.f;
		damage = 10.f;
		attackcooldown = 3.f;
		cost = 50.f;
	}
	else if (meshvalue == E_ARCHER)
	{
		float m_worldHeight = 100.f;
		float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		active = true;
		meshValue = SceneBase::GEO_ENEMY_ARCHER;
		scale.Set(20, 15, 1);
		vel.Set(-10.f, 0.f, 0.f);
		pos.Set(theScene->theAICastle->pos.x, theScene->theAICastle->pos.y - (theScene->theAICastle->scale.y / 3) + 2.f + theScene->enemy_yaxis, theScene->zaxis);
		enemyType = Enemy::E_ARCHER;
		hp = 50.f;
		range = 10.f;
		damage = 15.f;
		attackcooldown = 3.f;
		cost = 75.f;
	}
	else if (meshvalue == E_WIZARD)
	{
		float m_worldHeight = 100.f;
		float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		active = true;
		meshValue = SceneBase::GEO_ENEMY_WIZARD;
		scale.Set(10, 10, 1);
		vel.Set(-10.f, 0.f, 0.f);
		pos.Set(theScene->theAICastle->pos.x, theScene->theAICastle->pos.y - (theScene->theAICastle->scale.y / 3) + theScene->enemy_yaxis, theScene->zaxis);
		enemyType = Enemy::E_WIZARD;
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

Enemy::~Enemy()
{

}

void Enemy::update()
{
	//destroy enemy when it ran out of hp

	if (enemyType == ENEMY_TYPE::E_SOLDIER)
	{
		if (!StopToAttack)
		{
			pos += vel * theScene->_dt;
			meshValue = SceneBase::GEO_ENEMY_SOLDIER;
		}
		else
		{
			meshValue = SceneBase::GEO_ENEMY_SOLDIER_ATTACK;
		}
	}
	else if (enemyType == ENEMY_TYPE::E_ARCHER)
	{
		if (!StopToAttack)
		{
			pos += vel * theScene->_dt;
			meshValue = SceneBase::GEO_ENEMY_ARCHER;
		}
		else
		{
			meshValue = SceneBase::GEO_ENEMY_ARCHER_ATTACK;
		}
	}
	else if (enemyType == ENEMY_TYPE::E_WIZARD)
	{
		if (!StopToAttack)
		{
			pos += vel * theScene->_dt;
			meshValue = SceneBase::GEO_ENEMY_WIZARD;
		}
		else
		{
			meshValue = SceneBase::GEO_ENEMY_WIZARD_ATTACK;
		}
	}
	if (Attacked)
	{
		timer += theScene->_dt;
		if (timer > attackcooldown)
		{
			Attacked = false;
			timer = 0.0f;
			cout << "RESET" << endl;
		}
	}
	if (hp <= 0.f)
	{
		active = false;
	}

	if (pos.x <= 0)
	{
		active = false;
	}
	if (theScene->enemy_yaxis > 1.f)
	{
		theScene->enemy_yaxis = 0.005f;
	}
}

void Enemy::render()
{
	//glDisable(GL_DEPTH_TEST);
	theScene->modelStack.PushMatrix();
	theScene->modelStack.Translate(pos.x, pos.y, pos.z);
	theScene->modelStack.Scale(scale.x, scale.y, scale.z);
	theScene->RenderMesh(theScene->meshList[meshValue], false);
	theScene->modelStack.PopMatrix();
	//glEnable(GL_DEPTH_TEST);
}
