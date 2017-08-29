#include "EnemyAI.h"
#include "SceneBase.h"
#include "FileConfiguration.h"

EnemyAI::EnemyAI(SceneBase * scene, AI_LEVEL _levelAi)
	:theScene(scene)
	, levelAI(_levelAi)

{
}

EnemyAI::~EnemyAI()
{

}

void EnemyAI::Update(double dt)
{
	if (FileConfiguration::b_isLoadLevel == true)
		return;
	

	int steps = theScene->theAICastle->m_DefaultHp / theScene->theAICastle->hitpoints;

	timer += dt;
	if (timer >= 4.f)
	{
		timer = 0.0f;
		CreateEnemySoldier();
	}


	if (steps == 2 && Stage1surge1)
	{
		for (int a = 0; a < 6; a++)
		{
			CreateEnemySoldier();
		}
		Stage1surge1 = false;
		cout << "surge 1" << endl;
	}
	else if (steps == 5 && Stage1surge2)
	{
		for (int a = 0; a < 6; a++)
		{
			CreateEnemySoldier();
		}
		Stage1surge2 = false;
		cout << "surge 2" << endl;
	}
	//cout << "step " << steps << endl;
}


void EnemyAI::CreateEnemySoldier()
{
	//GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_SOLDIER);
	Enemy * tempEnemy = new Enemy(GameObject::GO_ENEMY, theScene, Enemy::E_SOLDIER);
	cout << theScene->theplayer->ReturnEnemyWallet() << endl;
	if (theScene->theplayer->ReturnEnemyWallet() > tempEnemy->cost)
	{
		theScene->theplayer->ReduceEnemyWalletAmount(tempEnemy->cost);
		theScene->theFactory->createGameObject(tempEnemy);
		cout << "Soldier" << endl;
		theScene->zaxis += 0.001f;
		theScene->enemy_yaxis += 0.05f;
		cout << "enemy " << theScene->zaxis << endl;
	}
	//delete tempEnemy;
}

void EnemyAI::CreateEnemyArcher()
{
	//GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_ARCHER);
	Enemy * tempEnemy = new Enemy(GameObject::GO_ENEMY, theScene, Enemy::E_ARCHER);
	cout << theScene->theplayer->ReturnEnemyWallet() << endl;
	if (theScene->theplayer->ReturnEnemyWallet() > tempEnemy->cost)
	{
		theScene->theplayer->ReduceEnemyWalletAmount(tempEnemy->cost);
		theScene->theFactory->createGameObject(tempEnemy);
		cout << "Archer" << endl;
		theScene->zaxis += 0.001f;
		theScene->enemy_yaxis += 0.05f;
		cout << "enemy " << theScene->zaxis << endl;
	}
}

void EnemyAI::CreateEnemyWizard()
{
	//GameObject *go = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_WIZARD);
	Enemy * tempEnemy = new Enemy(GameObject::GO_ENEMY, theScene, Enemy::E_WIZARD);
	cout << theScene->theplayer->ReturnEnemyWallet() << endl;
	if (theScene->theplayer->ReturnEnemyWallet() > tempEnemy->cost)
	{
		theScene->theplayer->ReduceEnemyWalletAmount(tempEnemy->cost);
		theScene->theFactory->createGameObject(tempEnemy);
		cout << "Wizard" << endl;
		theScene->zaxis += 0.001f;
		theScene->enemy_yaxis += 0.05f;
		cout << "enemy " << theScene->zaxis << endl;
	}
}

