#include "FileConfiguration.h"
#include "SceneBase.h"
#include "Enemy.h"
#include "PlayerTroops.h"
#include "Buildings.h"
#include "AICastle.h"

bool FileConfiguration::b_isLoadLevel = false;

void FileConfiguration::loadFile(string _fileName)
{
	ifstream myLoadFile;
	ifstream scoreFile;
	string eachLine;

	//Game Objects----------
	unsigned  tempType; // enum for GameObject type
	Vector3 tempPos; // GameObject position
	float tempHp; // GameObject Hp
	unsigned tempScore; // GameScore
	bool scoreLoaded = false;
	//Enemy  and player Troop variables 
	unsigned tempTroopType;
	float tempTimer;
	int tempStopAttack;
	int tempAttacked;
	float tempPlayerMoveX;
	float tempEnemyMoveX;

	//Buildings-----------
	float tempHitPoint;
	int tempCanFall;
	unsigned tempWallStackCounter;
	float tempGroundLevel;

	// count the number of lines 
	int counter = 0;


	myLoadFile.open(_fileName.c_str());

	if (!myLoadFile.is_open())
	{
		cout << "Impossile to open the file" << endl;
	}
	else if (myLoadFile.is_open())
	{
		if (myLoadFile.peek() == std::ifstream::traits_type::eof())
		{
			cout << "File is Empty, there is nothing to load " << endl;
		}
		else
		{

			//if (_fileName == "scorefile.txt")
			//{
			//	while (getline(myLoadFile, eachLine))
			//	{

			//		//store content of eachLine into ss
			//		istringstream ss(eachLine);
			//		string aToken = "";
			//		while (getline(ss, aToken, '\n'))
			//		{
			//			cout << aToken << endl;
			//			tempScore = stoi(aToken);
			//			_scene->m_highScore = tempScore;
			//		}
			//	}
			//}
			//else
			//{
			while (getline(myLoadFile, eachLine))
			{
				//store content of eachLine into ss
				istringstream ss(eachLine);
				string aToken = "";

				if (!eachLine.empty())
					counter++;

				// copy contents of ss into aToken until '=' is reached
				while (getline(ss, aToken, ':'))
				{
					string theTag = aToken;
					getline(ss, aToken, ':');


					//don't count  the line with Stage No and score
					if (theTag == "Stage No" || theTag == "Highscore1" || theTag == "Highscore2" || theTag == "Highscore3" || theTag == "Highscore4" || theTag == "Highscore5")
						counter--;

					if (theTag == "Highscore1")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[0] = tempScore;
					}
					if (theTag == "Highscore2")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[1] = tempScore;
					}
					if (theTag == "Highscore3")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[2] = tempScore;
					}
					if (theTag == "Highscore4")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[3] = tempScore;
					}
					if (theTag == "Highscore5")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[4] = tempScore;
					}

					//------- ENUM---------------//
					if (theTag == "GameObjectValue")
					{
						tempType = stoi(aToken);
					}
					else if (theTag == "Enemy Type")
					{
						tempTroopType = stoi(aToken);
					}
					else if (theTag == "Player Type")
					{
						tempTroopType = stoi(aToken);
					}

					//--------Vector3--------------//
					else if (theTag == "Position")
					{
						tempPos = Token2Vector(aToken);
					}



					// --------FLOAT----------------//
					else if (theTag == "Hp")
					{
						tempHp = stof(aToken);
					}
					else if (theTag == "Timer")
					{
						tempTimer = stof(aToken);
					}
					else if (theTag == "HitPoints")
					{
						tempHitPoint = stof(aToken);
					}
					else if (theTag == "PlayerMoveX")
					{
						tempPlayerMoveX = stof(aToken);
					}
					else if (theTag == "EnemyMoveX")
					{
						tempEnemyMoveX = stof(aToken);
					}
					else if (theTag == "GroundLevel")
					{
						tempGroundLevel = stof(aToken);
					}


					//--------Bool-------------//
					else if (theTag == "B_StopAttack")
					{
						tempStopAttack = stoi(aToken);
					}
					else if (theTag == "B_Attacked")
					{
						tempAttacked = stoi(aToken);
					}
					else if (theTag == "B_CanFall")
					{
						tempCanFall = stoi(aToken);
					}

					// -----------int ---------------
					else if (theTag == "WallStackCounter")
					{
						tempWallStackCounter = stoi(aToken);
					}


					// ----------------- 8 lines  for enemy and player----------------------//
					if (counter > 7 && (tempType == 5 || tempType == 6))
					{

						switch (tempType)
						{
						case 5:
						{
							Enemy * theEnemy;

							if (tempTroopType == 0)
							{
								theEnemy = new Enemy(GameObject::GO_ENEMY, _scene, Enemy::E_SOLDIER);
							}
							else if (tempTroopType == 1)
							{
								theEnemy = new Enemy(GameObject::GO_ENEMY, _scene, Enemy::E_ARCHER);
							}
							else if (tempTroopType == 2)
							{
								theEnemy = new Enemy(GameObject::GO_ENEMY, _scene, Enemy::E_WIZARD);
							}
							theEnemy->pos.Set(tempPos.x, tempPos.y, tempPos.z);
							theEnemy->hp = tempHp;
							theEnemy->timer = tempTimer;
							if (tempStopAttack == 0)
							{
								theEnemy->StopToAttack = false;
							}
							else
							{
								theEnemy->StopToAttack = true;
							}
							if (tempAttacked == 0)
							{
								theEnemy->Attacked = false;
							}
							else
							{
								theEnemy->Attacked = true;
							}

							theEnemy->enemyMoveX = tempEnemyMoveX;
							_scene->theFactory->createGameObject(theEnemy);
						}
						break;
						case 6:
						{
							PlayerTroop * theTroop;

							if (tempTroopType == 0)
							{
								theTroop = new PlayerTroop(GameObject::GO_PLAYER, _scene, PlayerTroop::P_SOLDIER);
							}
							else if (tempTroopType == 1)
							{
								theTroop = new PlayerTroop(GameObject::GO_PLAYER, _scene, PlayerTroop::P_ARCHER);
							}
							else if (tempTroopType == 2)
							{
								theTroop = new PlayerTroop(GameObject::GO_PLAYER, _scene, PlayerTroop::P_WIZARD);
							}
							theTroop->pos.Set(tempPos.x, tempPos.y, tempPos.z);
							theTroop->hp = tempHp;
							theTroop->timer = tempTimer;
							if (tempStopAttack == 0)
							{
								theTroop->StopToAttack = false;
							}
							else
							{
								theTroop->StopToAttack = true;
							}
							if (tempAttacked == 0)
							{
								theTroop->Attacked = false;
							}
							else
							{
								theTroop->Attacked = true;
							}
							theTroop->playerMoveX = tempPlayerMoveX;
							_scene->theFactory->createGameObject(theTroop);
						}
						break;
						}
						counter = 0;
					}

					// ----------------- 6 lines  for  player brick and AI brick----------------------//
					else if (counter > 5 && (tempType == 9 || tempType == 10))
					{

						switch (tempType)
						{
						case 9:
						{
							Buildings * thePlayerBrick = new Buildings(GameObject::GO_P_BRICK, _scene, tempWallStackCounter);
							thePlayerBrick->hitpoints = tempHitPoint;
							thePlayerBrick->pos = tempPos;
							thePlayerBrick->m_groundLevel = tempGroundLevel;
							if (tempCanFall == 0)
							{
								thePlayerBrick->m_canFall = false;
							}
							else
							{
								thePlayerBrick->m_canFall = true;
							}
							_scene->theFactory->createGameObject(thePlayerBrick);
						}
						break;
						case 10:
						{
							Buildings * theAIBrick = new Buildings(GameObject::GO_AI_BRICK, _scene, tempWallStackCounter);
							theAIBrick->hitpoints = tempHitPoint;
							theAIBrick->pos = tempPos;
							theAIBrick->m_groundLevel = tempGroundLevel;
							if (tempCanFall == 0)
							{
								theAIBrick->m_canFall = false;
							}
							else
							{
								theAIBrick->m_canFall = true;
							}
							_scene->theFactory->createGameObject(theAIBrick);
						}
						break;
						}

						counter = 0;
					}
					// ----------------- 2 lines  for  player castle and AI castle ----------------------//
					else if (counter > 2 && (tempType == 11 || tempType == 14))
					{

						// 11 - player castle
						// 14 - AI castle
						switch (tempType)
						{
						case 11:
						{
							Buildings * thePlayerCastle = new Buildings(GameObject::GO_P_CASTLE, _scene, tempWallStackCounter);
							thePlayerCastle->hitpoints = tempHitPoint;
							_scene->theFactory->createGameObject(thePlayerCastle);
						}
						break;
						case 14:
						{
							AICastle * theAIcastle = new AICastle(GameObject::GO_AI_CASTLE, _scene);
							theAIcastle->hitpoints = tempHitPoint;
							_scene->theFactory->createGameObject(theAIcastle);
						}
						break;
						}

					}
				}

			}
		}

	}

	myLoadFile.close();
}
void FileConfiguration::loadScoreFromFile(string _fileName)
{
	ifstream myLoadFile;
	ifstream scoreFile;
	string eachLine;
	unsigned tempScore;
	int counter = 0;


	myLoadFile.open(_fileName.c_str());

	if (!myLoadFile.is_open())
	{
		cout << "Impossile to open the file" << endl;
	}
	else if (myLoadFile.is_open())
	{
		if (myLoadFile.peek() == std::ifstream::traits_type::eof())
		{
			cout << "File is Empty, there is nothing to load " << endl;
		}
		else
		{
			while (getline(myLoadFile, eachLine))
			{
				//store content of eachLine into ss
				istringstream ss(eachLine);
				string aToken = "";

				if (!eachLine.empty())
					counter++;

				// copy contents of ss into aToken until '=' is reached
				while (getline(ss, aToken, ':'))
				{
					string theTag = aToken;
					getline(ss, aToken, ':');


					//don't count  the line with Stage No and score
					if (theTag == "Stage No" || theTag == "Highscore1" || theTag == "Highscore2" || theTag == "Highscore3" || theTag == "Highscore4" || theTag == "Highscore5")
						counter--;

					if (theTag == "Highscore1")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[0] = tempScore;
					}
					if (theTag == "Highscore2")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[1] = tempScore;
					}
					if (theTag == "Highscore3")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[2] = tempScore;
					}
					if (theTag == "Highscore4")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[3] = tempScore;
					}
					if (theTag == "Highscore5")
					{
						tempScore = stoi(aToken);
						_scene->m_highScore[4] = tempScore;
					}
				}
			}
		}
	}
	myLoadFile.close();
}


void FileConfiguration::saveFile(string _fileName)
{
	ofstream outPutFile;
	outPutFile.open(_fileName.c_str());

	if (!outPutFile.is_open())
	{
		cout << "Impossile to open the file" << endl;
	}
	else
	{
		cout << "Saved file successfully" << endl;
	
			//Save the current Stage
			outPutFile << "Highscore1:" << _scene->m_highScore[0] << endl;
			outPutFile << "Highscore2:" << _scene->m_highScore[1] << endl;
			outPutFile << "Highscore3:" << _scene->m_highScore[2] << endl;
			outPutFile << "Highscore4:" << _scene->m_highScore[3] << endl;
			outPutFile << "Highscore5:" << _scene->m_highScore[4] << endl;
			outPutFile << "Stage No:" << _scene->sceneNumber << endl;
			outPutFile << endl;
			outPutFile << endl;

             //save objects in factory container
			for (auto & it : _scene->theFactory->g_FactoryMap)
			{
				if (it.second->active == false)
					continue;

				if (it.first == GameObject::GO_ENEMY)
				{
					outPutFile << "GameObjectValue:" << it.first << endl;
					outPutFile << "Enemy Type:" << static_cast<Enemy*>(it.second)->enemyType << endl;
					outPutFile << "Position:" << it.second->pos << endl;
					outPutFile << "Hp:" << static_cast<Enemy*>(it.second)->hp << endl;
					outPutFile << "Timer:" << static_cast<Enemy*>(it.second)->timer << endl;
					outPutFile << "B_StopAttack:" << static_cast<Enemy*>(it.second)->StopToAttack << endl;
					outPutFile << "B_Attacked:" << static_cast<Enemy*>(it.second)->Attacked << endl;
					outPutFile << "EnemyMoveX:" << static_cast<Enemy*>(it.second)->enemyMoveX << endl;
					outPutFile << endl;
					outPutFile << endl;
				}
				else if (it.first == GameObject::GO_PLAYER)
				{
					outPutFile << "GameObjectValue:" << it.first << endl;
					outPutFile << "Player Type:" << static_cast<PlayerTroop*>(it.second)->playerType << endl;
					outPutFile << "Position:" << it.second->pos << endl;
					outPutFile << "Hp:" << static_cast<PlayerTroop*>(it.second)->hp << endl;
					outPutFile << "Timer:" << static_cast<PlayerTroop*>(it.second)->timer << endl;
					outPutFile << "B_StopAttack:" << static_cast<PlayerTroop*>(it.second)->StopToAttack << endl;
					outPutFile << "B_Attacked:" << static_cast<PlayerTroop*>(it.second)->Attacked << endl;
					outPutFile << "PlayerMoveX:" << static_cast<PlayerTroop*>(it.second)->playerMoveX << endl;
					outPutFile << endl;
					outPutFile << endl;
				}
			}

			// save objects in building container
			for (auto & it : _scene->theFactory->g_BuildingsVector)
			{
				if (it->active == false)
					continue;

				outPutFile << "GameObjectValue:" << it->type << endl;
				outPutFile << "HitPoints:" << it->hitpoints << endl;
				// only store m_canFall for player and enemy brick
				if (it->type == GameObject::GO_P_BRICK || it->type == GameObject::GO_AI_BRICK)
				{
					outPutFile << "B_CanFall:" << it->m_canFall << endl;
					outPutFile << "Position:" << it->pos << endl;
					outPutFile << "GroundLevel:" << it->m_groundLevel << endl;
				}
				// only store wallcounter for  player brick and enemy brick and player castle
				if (it->type != GameObject::GO_AI_CASTLE)
					outPutFile << "WallStackCounter:" << it->getInitialOffset() << endl;
				outPutFile << endl;
				outPutFile << endl;
			}
		}

	
	outPutFile.close();

}

void FileConfiguration::loadLevel(string _fileName)
{
	// static bool variable to determine whether to load level
	b_isLoadLevel = true;

	ifstream myLoadFile;
	string eachLine;

	myLoadFile.open(_fileName.c_str());

	if (!myLoadFile.is_open())
	{
		cout << "Impossile to open the file" << endl;
	}
	else if (myLoadFile.is_open())
	{
		if (myLoadFile.peek() == std::ifstream::traits_type::eof())
		{
			cout << "File is Empty, there is nothing to load " << endl;
		}
		else
		{
			cout << "Load  Successfully" << endl;
			while (getline(myLoadFile, eachLine))
			{
				istringstream ss(eachLine);
				string aToken = "";

				// copy contents of ss into aToken until '=' is reached
				while (getline(ss, aToken, ':'))
				{
					string theTag = aToken;
					getline(ss, aToken, ':');

					if (theTag == "Stage No")
					{
						currentStage = stoi(aToken);
					}

				}
			}
		}
	}

	myLoadFile.close();
}


double FileConfiguration::Token2Double(string token)
{
	return atof(token.c_str());
}

Vector3 FileConfiguration::Token2Vector(string token)
{
	Vector3 tempVector;

	istringstream ss(token);
	string aToken = "";

	getline(ss, aToken, '[');
	getline(ss, aToken, ',');
	tempVector.x = Token2Double(aToken);
	getline(ss, aToken, ',');
	tempVector.y = Token2Double(aToken);
	getline(ss, aToken, ',');
	tempVector.z = Token2Double(aToken);


	return tempVector;
}

FileConfiguration::FileConfiguration()
{
}

FileConfiguration::~FileConfiguration()
{

}

void FileConfiguration::setScene(SceneBase * scene)
{
	_scene = scene;
}
