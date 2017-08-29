#include "EnemyAI.h"
#include "SceneBase.h"

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
	/*float steps = theScene->theAICastle->m_DefaultHp / theScene->theAICastle->hitpoints;*/
	timer += dt;
	if (timer >= 5.f)
	{
		timer = 0.0f;
		CreateEnemySoldier();
	}
	//if (steps > 2 && steps < 3|| steps > 3 && steps < 4|| steps > 4 && steps < 5|| steps > 5)
	//{
	//	surge = true;
	//	//for (int a = 0; a < 2; a++)
	//	//{
	//	//	CreateEnemySoldier();
	//	//	CreateEnemyArcher();
	//	//}
	//}
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
		cout << theScene->zaxis << endl;
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
		cout << theScene->zaxis << endl;
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
		cout << theScene->zaxis << endl;
	}
}

