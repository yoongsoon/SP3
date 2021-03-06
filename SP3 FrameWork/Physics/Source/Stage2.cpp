
#include "Stage2.h"
#include "GL\glew.h"
#include "Application.h"
#include "SceneManager.h"
#include "WeaponInfo.h"
#include "PlayerInfo.h"
#include "Cannon.h"
#include "Catapult.h"
#include "Bow.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

Stage2 * Stage2::sInstance = new Stage2(SceneManager::getInstance());

Stage2::Stage2(SceneManager * _scene)
{
	_scene->AddScene("Stage2", this);
}

Stage2::~Stage2()
{
}

void Stage2::Init()
{
	SceneBase::Init();

	for (int i = 0; i < 5; ++i)
	{
		m_highScore[i] = 0;
	}


	m_sceneID = SceneBase::SC_02;
	ghost_exist = false;
	release_ghost_exist = false;
	M_ghost_exist = false;
	canPredict = true;
	weap_manager = NULL;
	P_rotation = 1.f;
	//Projectile_to_rotate_test = 1.f;
	//Physics code here
	m_speed = 1.f;
	m_levelScore = 10000;
	zaxis = 1.f;

	//theFile->loadFile("scorefile.txt");

	Math::InitRNG();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Create Sound Engine to the play sounds
	CSoundEngine::getInstance()->Init();
	CSoundEngine::getInstance()->AddSound("BackGround Music", "Sound//Crossroads.ogg");
	CSoundEngine::getInstance()->PlayASound("BackGround Music", true, false);
	CSoundEngine::getInstance()->theCurrentSound->setVolume(0.4f);


	//initialise the factory class
	// MUST BE FIRST!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	theFactory = new Factory();

	//MiniMap
	theMiniMap = new MiniMap(GameObject::GO_MINI_MAP, this);

	theCollider = new CollisionManager(this);
	//intialise ghost projectile prediction
	thePredictionLine = new GameObject*[10];
	for (size_t i = 0; i < 10; i++)
	{
		thePredictionLine[i] = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
		theFactory->createGameObject(thePredictionLine[i]);
	}
	//initialize ghosts
	theGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
	theFactory->createGameObject(theGhostProj);

	theReleaseMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
	theFactory->createGameObject(theReleaseMouseGhostProj);

	theMouseGhostProj = new Projectile(Projectile::GHOST_PROJECTILE, GameObject::GO_P_PROJECTILE, this);
	theMouseGhostProj->active = true;
	theFactory->createGameObject(theMouseGhostProj);


	// if there is a previous load data , DON"T reinitialise the buildings
	if (FileConfiguration::b_isLoadLevel == false)
	{
		// BUILDINGS
		for (int m_wallStackCounter = 1; m_wallStackCounter <= 6; ++m_wallStackCounter)
		{
			Buildings * theWall = new Buildings(GameObject::GO_P_BRICK, this, m_wallStackCounter);
			theFactory->createGameObject(theWall);
		}
		theCastle = new Buildings(GameObject::GO_P_CASTLE, this, 0);
		theFactory->createGameObject(theCastle);

		for (int m_wallStackCounter = 1; m_wallStackCounter <= 6; ++m_wallStackCounter)
		{
			Buildings * theWall = new Buildings(GameObject::GO_AI_BRICK, this, m_wallStackCounter);
			theFactory->createGameObject(theWall);
		}
		theAICastle = new AICastle(GameObject::GO_AI_CASTLE, this);
		theFactory->createGameObject(theAICastle);
	}

	theEnemyAI = new EnemyAI(this, EnemyAI::STAGE_1);
	BackGround * theBackGround = new BackGround(BackGround::BACK_GROUND_STAGE2, GameObject::GO_NONE, this);
	theFactory->createGameObject(theBackGround);

	theplayer = new Player();
	theplayer->setScene(this);

	theEnemy = new Enemy(GameObject::GO_ENEMY, this, Enemy::E_SOLDIER);

	gom = new GameObjectManager(this);

	/*scenebase = new SceneBase();*/

	//player itself
	thePlayer = new PlayerInfo();
	thePlayer->Init();

	SpriteAnimation* wizard = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD]);
	SpriteAnimation* wizardattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD_ATTACK]);
	SpriteAnimation* archer = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER]);
	SpriteAnimation* archerattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER_ATTACK]);
	SpriteAnimation* soldier = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER]);
	SpriteAnimation* soldierattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER_ATTACK]);

	SpriteAnimation* enemywizard = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_WIZARD]);
	SpriteAnimation* enemywizardattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_WIZARD_ATTACK]);
	SpriteAnimation* enemyarcher = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_ARCHER]);
	SpriteAnimation* enemyarcherattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_ARCHER_ATTACK]);
	SpriteAnimation* enemysoldier = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_SOLDIER]);
	SpriteAnimation* enemysoldierattack = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_SOLDIER_ATTACK]);

	SpriteAnimation* P_Bow_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_BOW_ARROW]);
	SpriteAnimation* P_Catapult_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_CATAPULT_ROCKS]);
	//Sprite Animation init
	if (wizard)
	{
		wizard->m_anim = new Animation();
		wizard->m_anim->Set(0, 5, 0, 1.0f, true);
	}
	if (wizardattack)
	{
		wizardattack->m_anim = new Animation();
		wizardattack->m_anim->Set(0, 8, 0, 1.0f, true);
	}
	if (archer)
	{
		archer->m_anim = new Animation();
		archer->m_anim->Set(0, 3, 0, 1.0f, true);
	}
	if (archerattack)
	{
		archerattack->m_anim = new Animation();
		archerattack->m_anim->Set(0, 2, 0, 1.0f, true);
	}
	if (soldier)
	{
		soldier->m_anim = new Animation();
		soldier->m_anim->Set(0, 5, 0, 1.0f, true);
	}
	if (soldierattack)
	{
		soldierattack->m_anim = new Animation();
		soldierattack->m_anim->Set(0, 4, 0, 1.0f, true);
	}

	if (enemywizard)
	{
		enemywizard->m_anim = new Animation();
		enemywizard->m_anim->Set(0, 5, 0, 1.0f, true);
	}
	if (enemywizardattack)
	{
		enemywizardattack->m_anim = new Animation();
		enemywizardattack->m_anim->Set(0, 8, 0, 1.0f, true);
	}
	if (enemyarcher)
	{
		enemyarcher->m_anim = new Animation();
		enemyarcher->m_anim->Set(0, 3, 0, 1.0f, true);
	}
	if (enemyarcherattack)
	{
		enemyarcherattack->m_anim = new Animation();
		enemyarcherattack->m_anim->Set(0, 2, 0, 1.0f, true);
	}
	if (enemysoldier)
	{
		enemysoldier->m_anim = new Animation();
		enemysoldier->m_anim->Set(0, 5, 0, 1.0f, true);
	}
	if (enemysoldierattack)
	{
		enemysoldierattack->m_anim = new Animation();
		enemysoldierattack->m_anim->Set(0, 4, 0, 1.0f, true);
	}
	//if (P_Bow_Sprite)
	//{
	P_Bow_Sprite->m_anim = new Animation();
	P_Bow_Sprite->m_anim->Set(0, 12, 0, 1.0f, true);
	//}
	//	if (P_Cannon_Sprite)
	//	{
	//		P_Cannon_Sprite->m_anim = new Animation();
	//		P_Cannon_Sprite->m_anim->Set(0, 15, 0, 1.0f, true);
	//	}
	if (P_Catapult_Sprite)
	{
		P_Catapult_Sprite->m_anim = new Animation();
		P_Catapult_Sprite->m_anim->Set(2, 9, 0, 1.0f, true);
	}

	theUIManager = new UIManager(this);

	//Init scene
	theFile->setScene(this);
	theFile->loadScoreFromFile("Data.txt");
	// if the load function is called , then load file
	if (FileConfiguration::b_isLoadLevel == true)
		theFile->loadFile("Data.txt");

	//enum variable use to load scene from main menu
	sceneNumber = SC_02;
	//static variable use for switching scene in lose scene
	stageNo = 2;
}

void Stage2::Update(double dt)
{
	_elapsedTime += (float)dt;
	pressDelay += (float)dt;
	_dt = (float)dt;

	//Calculating aspect ratio ( 4:3)
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	if (Application::IsKeyPressed('K') && pressDelay >= cooldownPressed)
	{

		for (int i = 0; i < 5; ++i)
		{
			if (m_levelScore > m_highScore[i])
			{
				m_highScore[i] = m_levelScore;
				break;
			}
		}
		//theFile->saveFile("scorefile.txt");

		theFile->saveFile("Data.txt");
		pressDelay = 0.f;
	}
	if (Application::IsKeyPressed('L') && pressDelay >= cooldownPressed)
	{
		//theFile->loadFile("scorefile.txt");
		theFile->loadFile("Data.txt");
		pressDelay = 0.f;
	}



	if ((b_isPause == false) && (b_isWon == false))
	{
		m_levelScore -= (float)dt * 0.5f;

		CSoundEngine::getInstance()->theCurrentSound->setIsPaused(false);

		//CSoundEngine::getInstance()->PauseSounds("BackGround Music");

		static bool bow = false;
		if (Application::IsKeyPressed(VK_NUMPAD1) && !bow)
		{
			//curr_weapon = 0;
			thePlayer->SetWeapon(0);
			bow = true;

			weapon1 = true;

			weapon2 = false;
			weapon3 = false;
		}
		else if (!Application::IsKeyPressed(VK_NUMPAD1) && bow)
		{
			bow = false;
		}
		if (Application::IsKeyPressed(VK_NUMPAD2) && !bow)
		{
			//curr_weapon = 1;
			thePlayer->SetWeapon(1);
			bow = true;

			weapon2 = true;

			weapon1 = false;
			weapon3 = false;
		}
		else if (!Application::IsKeyPressed(VK_NUMPAD2) && bow)
		{
			bow = false;
		}
		if (Application::IsKeyPressed(VK_NUMPAD3) && !bow)
		{
			//curr_weapon = 2;
			thePlayer->SetWeapon(2);
			bow = true;

			weapon3 = true;

			weapon1 = false;
			weapon2 = false;
		}
		else if (!Application::IsKeyPressed(VK_NUMPAD3) && bow)
		{
			bow = false;
		}
		/*	static bool onepress = false;
		if (Application::IsKeyPressed('1') && !onepress)
		{
		CreateEnemySoldier();
		onepress = true;
		}
		else if (!Application::IsKeyPressed('1') && onepress)
		{
		onepress = false;
		}
		static bool twopress = false;
		if (Application::IsKeyPressed('2') && !twopress)
		{
		CreateEnemyArcher();
		twopress = true;
		}
		else if (!Application::IsKeyPressed('2') && twopress)
		{
		twopress = false;
		}
		static bool threepress = false;
		if (Application::IsKeyPressed('3') && !threepress)
		{
		CreateEnemyWizard();
		threepress = true;
		}
		else if (!Application::IsKeyPressed('3') && threepress)
		{
		threepress = false;
		}
		*/
		static bool fourpress = false;
		if (Application::IsMousePressed(1) && !fourpress)
		{
			// 48.5 middle x position of the soldier image
			if (currentPos.x >= 42.5f && currentPos.x <= 56.5f
				&& currentPos.y >= 3.0f && currentPos.y <= 18.0f)
			{
				CreateFriendlySoldier();
				fourpress = true;
				/*	SceneManager::getInstance()->SetActiveScene("MainMenu");*/
			}
			// 68.5 middle x position of the arhcer image
			else if (currentPos.x >= 59.5f && currentPos.x <= 73.5f
				&& currentPos.y >= 3.0f && currentPos.y <= 18.0f)
			{
				CreateFriendlyArcher();
				fourpress = true;
			}
			// 88.5 middle x position of the wizard image
			else if (currentPos.x >= 76.5f && currentPos.x <= 90.0f
				&& currentPos.y >= 3.0f && currentPos.y <= 18.0f)
			{
				CreateFriendlyWizard();
				fourpress = true;
			}

		}
		else if (!Application::IsMousePressed(1) && fourpress)
		{
			fourpress = false;
		}

		/*	static bool fourpress = false;
		if (Application::IsKeyPressed('4') && !fourpress)
		{
		CreateFriendlySoldier();
		fourpress = true;
		}
		else if (!Application::IsKeyPressed('4') && fourpress)
		{
		fourpress = false;
		}
		static bool fivepress = false;
		if (Application::IsKeyPressed('5') && !fivepress)
		{
		CreateFriendlyArcher();
		fivepress = true;
		}
		else if (!Application::IsKeyPressed('5') && fivepress)
		{
		fivepress = false;
		}
		static bool sixpress = false;
		if (Application::IsKeyPressed('6') && !sixpress)
		{
		CreateFriendlyWizard();
		sixpress = true;
		}
		else if (!Application::IsKeyPressed('6') && sixpress)
		{
		sixpress = false;
		}*/

		//Mouse Section
		Application::GetCursorPos(&mouseX, &mouseY);
		currentPos.x = (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
		currentPos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;

		static bool bLButtonState = false;
		//to only create ghosts balls ONCE not every update
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;

			Application::GetCursorPos(&mouseX, &mouseY);
			//places current mouse pos and fixes to the pos where mouse clicked
			theGhostProj->pos = currentPos;// (float)mouseX / Application::GetWindowWidth() * m_worldWidth;
										   //	theGhostProj->pos.y = (Application::GetWindowHeight() - (float)mouseY) / Application::GetWindowHeight() * m_worldHeight;
										   //theGhostProj->active = true;
										   //changes prev mouse ghost
			theReleaseMouseGhostProj->active = false;


		}
		else if (bLButtonState && !Application::IsMousePressed(0))
		{
			bLButtonState = false;
			//when mouseclick release it renders wwhere the mouse was released 
			theReleaseMouseGhostProj->pos = currentPos;
			//theReleaseMouseGhostProj->active = true;
			//theGhostProj->active = false;
			//shoots projectile
			thePlayer->DischargePPTEST(theGhostProj->pos, currentPos, this);

			if (weapon3)
			{
				fire = true;
			}

		}

		//shows where mouse is(if need remove mouse cursor)
		theMouseGhostProj->pos = currentPos;
		//prediction line when hold leftclick
		if (bLButtonState)
		{
			for (size_t i = 0; i < 10; i++)
			{
				double tline = i * 0.10;
				thePredictionLine[i]->pos.y = (((50) + ((theGhostProj->pos.y - theMouseGhostProj->pos.y) * tline)) + ((-9.8 *(tline * tline)) / 2));
				thePredictionLine[i]->pos.x = (20) + ((theGhostProj->pos.x - theMouseGhostProj->pos.x) * tline);
				thePredictionLine[i]->pos.z = 5.0f;
				thePredictionLine[i]->scale = Vector3((i + 1)*0.1, (i + 1)*0.1, (i + 1)*0.1);
				thePredictionLine[i]->active = true;
			}
			P_rotation = Math::RadianToDegree(atan2f(theGhostProj->pos.y - theMouseGhostProj->pos.y, theGhostProj->pos.x - theMouseGhostProj->pos.x));
		}
		else
		{
			//90 points up+
			P_rotation = 0;
			//-90 points down
		}
		// scrolling right
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			//theMouseGhostProj->pos.x += _dt * 50;
			camera.position.x += _dt * 80;
			camera.target.x += _dt * 80;
		}
		// scrolling left
		if (Application::IsKeyPressed(VK_LEFT))
		{
			//theMouseGhostProj->pos.x -= _dt * 50;
			camera.position.x -= _dt * 80;
			camera.target.x -= _dt * 80;
		}
		theMouseGhostProj->active = false;

		//clamp camera position and target between World X coordinate 0 and m_world *2
		camera.position.x = Math::Clamp(camera.position.x, 0.f, m_worldWidth * 2);
		camera.target.x = Math::Clamp(camera.target.x, 0.f, m_worldWidth * 2);

		//Update all Game Objects
		theFactory->updateGameObject();
		// Update collisions
		theCollider->Update(dt);
		theEnemyAI->Update(dt);

		gom->update();
		//player units
		theplayer->update();
		//playerinfo
		thePlayer->Update(dt);

		theMiniMap->Update();

		SpriteAnimation** sprite = new SpriteAnimation*[12];
		sprite[0] = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD]);
		sprite[1] = dynamic_cast<SpriteAnimation*>(meshList[GEO_WIZARD_ATTACK]);
		sprite[2] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER]);
		sprite[3] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ARCHER_ATTACK]);
		sprite[4] = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER]);
		sprite[5] = dynamic_cast<SpriteAnimation*>(meshList[GEO_SOLDIER_ATTACK]);

		sprite[6] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_WIZARD]);
		sprite[7] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_WIZARD_ATTACK]);
		sprite[8] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_ARCHER]);
		sprite[9] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_ARCHER_ATTACK]);
		sprite[10] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_SOLDIER]);
		sprite[11] = dynamic_cast<SpriteAnimation*>(meshList[GEO_ENEMY_SOLDIER_ATTACK]);

		SpriteAnimation* P_Bow_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_BOW_ARROW]);
		SpriteAnimation* P_Catapult_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_CATAPULT_ROCKS]);
		//Sprite Animation update
		for (int a = 0; a < 12; a++)
		{
			sprite[a]->Update(dt);
			sprite[a]->m_anim->animActive = true;
			//cout << theEnemy->Attacked << endl;
		}

		//distance of click and drag
		double result = sqrt(((theGhostProj->pos.x - theMouseGhostProj->pos.x)*(theGhostProj->pos.x - theMouseGhostProj->pos.x)) + ((theGhostProj->pos.y - theMouseGhostProj->pos.y)*(theGhostProj->pos.y - theMouseGhostProj->pos.y)));

		if (!bLButtonState && !fire)
		{
			P_Bow_Sprite->m_currentFrame = 0;
			P_Catapult_Sprite->m_currentFrame = 0;
		}
		else if ((bLButtonState) && (result > 50))
		{
			P_Bow_Sprite->m_currentFrame = 11;
		}
		else if ((bLButtonState) && (result > 45))
		{
			P_Bow_Sprite->m_currentFrame = 10;
		}
		else if ((bLButtonState) && (result > 40))
		{
			P_Bow_Sprite->m_currentFrame = 9;
		}
		else if ((bLButtonState) && (result > 35))
		{
			P_Bow_Sprite->m_currentFrame = 8;
			P_Catapult_Sprite->m_currentFrame = 2;
		}
		else if ((bLButtonState) && (result > 30))
		{
			P_Bow_Sprite->m_currentFrame = 7;
		}
		else if ((bLButtonState) && (result > 25))
		{
			P_Bow_Sprite->m_currentFrame = 6;
			P_Catapult_Sprite->m_currentFrame = 1;
		}
		else if ((bLButtonState) && (result > 20))
		{
			P_Bow_Sprite->m_currentFrame = 5;
		}
		else if ((bLButtonState) && (result > 15))
		{
			P_Bow_Sprite->m_currentFrame = 4;
		}
		else if ((bLButtonState) && (result > 10))
		{
			P_Bow_Sprite->m_currentFrame = 3;
			P_Catapult_Sprite->m_currentFrame = 0;
		}
		else if ((bLButtonState) && (result > 5))
		{
			P_Bow_Sprite->m_currentFrame = 2;
		}
		else if ((bLButtonState) && (result > 1))
		{
			P_Bow_Sprite->m_currentFrame = 1;
		}
		P_Bow_Sprite->m_anim->animActive = true;

		P_Catapult_Sprite->Update(dt);
		if ((fire) && (!thePlayer->weap_manager[2]->Get_b_Fire()))
		{
			P_Catapult_Sprite->m_anim->animActive = true;
			if (P_Catapult_Sprite->m_currentFrame > 8)
			{
				fire = false;
			}

		}
		else if ((!fire) && (thePlayer->weap_manager[2]->Get_b_Fire()))
		{
			P_Catapult_Sprite->m_anim->animActive = false;

		}
	}
	else
	{
		CSoundEngine::getInstance()->theCurrentSound->setIsPaused();
	}

	//win the game
	if (m_levelScore <= 0)
	{
		b_isWon = true;
	}
	theUIManager->Update();
	theUIManager->UpdateText();

	if (theAICastle->isDead)
	{
		FileConfiguration::b_isLoadLevel = false;
		SceneManager::getInstance()->SetActiveScene("Stage2");
	}
}

void Stage2::Render()
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


	//Render the all Game Objects
	theFactory->renderGameObject();

	theMiniMap->RenderUI();


	//modelStack.PushMatrix();
	//modelStack.Translate(100.f, 25.f, 2.f);
	//modelStack.Scale(100.f, 50.f, 1.f);
	//RenderMesh(meshList[GEO_TERRAIN], false);
	//modelStack.PopMatrix();


	theUIManager->Render();
	theUIManager->RenderText();

	SpriteAnimation* P_Catapult_Sprite = dynamic_cast<SpriteAnimation*>(meshList[GEO_P_CATAPULT_ROCKS]);


	//rendering problem
	if ((weapon1))
	{
		modelStack.PushMatrix();
		modelStack.Translate(20.0f, 50.0f, zaxis);
		modelStack.Rotate(P_rotation, 0, 0, 1);
		modelStack.Scale(15.0f, 15.0f, 1.0f);
		RenderMesh(meshList[GEO_P_BOW_ARROW], false);
		modelStack.PopMatrix();
		zaxis += 0.001;
	}
	if ((weapon2))
	{
		modelStack.PushMatrix();
		modelStack.Translate(20.0f, 50.0f, zaxis);
		modelStack.Rotate(P_rotation, 0, 0, 1);
		modelStack.Scale(15.0f, 15.0f, 1.0f);
		RenderMesh(meshList[GEO_P_CANNON], false);
		modelStack.PopMatrix();
		zaxis += 0.001;

		modelStack.PushMatrix();
		modelStack.Translate(20.0f, 50.0f, zaxis);
		modelStack.Scale(15.0f, 15.0f, 1.0f);
		RenderMesh(meshList[GEO_P_CANNON_STAND], false);
		modelStack.PopMatrix();
		zaxis += 0.001;
	}
	if ((weapon3))
	{
		modelStack.PushMatrix();
		modelStack.Translate(17.0f, 47.0f, zaxis);
		modelStack.Scale(15.0f, 15.0f, 1.0f);
		RenderMesh(meshList[GEO_P_CATAPULT_ROCKS], false);
		modelStack.PopMatrix();
		zaxis += 0.001;
	}

}

void Stage2::Exit()
{
	//Clearing the memory
	if (theplayer)
	{
		delete theplayer;
	}

	if (thePlayer)
	{
		delete thePlayer;
	}

	if (theUIManager)
	{
		delete theUIManager;
	}

	if (theMiniMap)
	{
		delete theMiniMap;
	}

	if (theCollider)
	{
		delete theCollider;
	}


	CSoundEngine::getInstance()->Exit();
	FileConfiguration::b_isLoadLevel = false;
	SceneBase::Exit();
}


void Stage2::CreateFriendlySoldier()
{
	//GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_SOLDIER);
	PlayerTroop * tempPlayer = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_SOLDIER);
	cout << theplayer->ReturnWallet() << endl;
	if (theplayer->ReturnWallet() > tempPlayer->cost)
	{
		theplayer->ReduceWalletAmount(tempPlayer->cost);
		theFactory->createGameObject(tempPlayer);
		cout << "friend Soldier" << endl;
		zaxis += 0.001f;
		player_yaxis += 0.05f;
		cout << zaxis << endl;
	}
}

void Stage2::CreateFriendlyArcher()
{
	//GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_ARCHER);
	PlayerTroop * tempPlayer = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_ARCHER);
	cout << theplayer->ReturnWallet() << endl;
	if (theplayer->ReturnWallet() > tempPlayer->cost)
	{
		theplayer->ReduceWalletAmount(tempPlayer->cost);
		theFactory->createGameObject(tempPlayer);
		cout << "friend Archer" << endl;
		zaxis += 0.001f;
		player_yaxis += 0.05f;
		cout << zaxis << endl;
	}
}

void Stage2::CreateFriendlyWizard()
{
	//GameObject *go = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_WIZARD);
	PlayerTroop * tempPlayer = new PlayerTroop(GameObject::GO_PLAYER, this, PlayerTroop::P_WIZARD);
	cout << theplayer->ReturnWallet() << endl;
	if (theplayer->ReturnWallet() > tempPlayer->cost)
	{
		theplayer->ReduceWalletAmount(tempPlayer->cost);
		theFactory->createGameObject(tempPlayer);
		cout << "friend Wizard" << endl;
		player_yaxis += 0.05f;
		zaxis += 0.001f;
		cout << zaxis << endl;
	}
}
