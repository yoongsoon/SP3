#include "FileConfiguration.h"
#include "SceneBase.h"
#include "Enemy.h"
#include "PlayerTroops.h"
#include "Buildings.h"

void FileConfiguration::loadFile(string _fileName)
{
	ifstream myLoadFile;
	string eachLine;

	//Game Objects----------
	unsigned  tempType; // enum for GameObject type
	Vector3 tempPos; // GameObject position
	float tempHp; // GameObject Hp
	unsigned score; // GameScore

	//Enemy  and player Troop variables 
	unsigned tempTroopType;
	float tempTimer;
	bool tempStopAttack; 
	bool tempAttacked; 
	float tempPlayerMoveX;
	float tempEnemyMoveX;
	
	//Buildings-----------
	float tempHitPoint;
	bool tempGravity;

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
			cout << "Load  Successfully" << endl;
			while (getline(myLoadFile, eachLine))
			{
				//store content of eachLine into ss
				istringstream ss(eachLine);
				string aToken = "";

				if(!eachLine.empty())
				counter++;

				// copy contents of ss into aToken until '=' is reached
				while (getline(ss, aToken, ':'))
				{
					string theTag = aToken;
					getline(ss, aToken, ':');


					//------- ENUM---------------//
					if (theTag == "HighScore")
					{
						tempType = stoi(aToken);
					}
					else if (theTag == "GameObjectValue")
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
				

					//--------Bool-------------//
					else if (theTag == "B_StopAttack")
					{
						tempStopAttack = stoi(aToken);
					}
					else if (theTag == "B_Attacked")
					{
						tempAttacked = stoi(aToken);
					}
					else if (theTag == "B_Gravity")
					{
						tempGravity = stoi(aToken);
					}

					if (counter > 8)
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
							theEnemy->StopToAttack = tempStopAttack;
							theEnemy->Attacked = tempAttacked;
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
							theTroop->pos.Set(tempPos.x , tempPos.y , tempPos.z);
							theTroop->hp = tempHp;
							theTroop->timer = tempTimer;
							theTroop->StopToAttack = tempStopAttack;
							theTroop->Attacked = tempAttacked;
							theTroop->playerMoveX = tempPlayerMoveX;
							_scene->theFactory->createGameObject(theTroop);
						}
						break;

						}

						counter = 0;
					}

				}
			}
		}
	}
}

void FileConfiguration::saveFile(string _fileName)
{
	ofstream outPutFile;
	bool ScoreSaved = false;
	outPutFile.open(_fileName.c_str());

	if (!outPutFile.is_open())
	{
		cout << "Impossile to open the file" << endl;
	}
	else
	{
		cout << "Saved file successfully" << endl;
		//outPutFile << "HighScore:" << 
		for (auto & it : _scene->theFactory->g_FactoryMap)
		{
			if (it.second->active == false)
				continue;

			if (it.first == GameObject::GO_ENEMY)
			{
				outPutFile << "GameObjectValue:" << it.first << endl;
				outPutFile <<"Enemy Type:"<< static_cast<Enemy*>(it.second)->enemyType << endl;
				outPutFile <<"Position:"<<it.second->pos << endl;
				outPutFile <<"Hp:"<< static_cast<Enemy*>(it.second)->hp << endl;
				outPutFile << "Timer:"<<static_cast<Enemy*>(it.second)->timer << endl;
				outPutFile << "B_StopAttack:" << static_cast<Enemy*>(it.second)->StopToAttack << endl;
				outPutFile << "B_Attacked:"<<static_cast<Enemy*>(it.second)->Attacked << endl;
				outPutFile << "EnemyMoveX:" << static_cast<Enemy*>(it.second)->enemyMoveX << endl;
				outPutFile << endl;
				outPutFile << endl;
			}
			else if (it.first == GameObject::GO_PLAYER)
			{
				outPutFile << "GameObjectValue:" << it.first << endl;
				outPutFile <<"Player Type:"<<static_cast<PlayerTroop*>(it.second)->playerType << endl;
				outPutFile << "Position:" << it.second->pos << endl;
				outPutFile << "Hp:"<<static_cast<PlayerTroop*>(it.second)->hp << endl;
				outPutFile <<"Timer:"<<static_cast<PlayerTroop*>(it.second)->timer << endl;
				outPutFile << "B_StopAttack:" << static_cast<PlayerTroop*>(it.second)->StopToAttack << endl;
				outPutFile << "B_Attacked:" << static_cast<PlayerTroop*>(it.second)->Attacked << endl;
				outPutFile << "PlayerMoveX:" << static_cast<PlayerTroop*>(it.second)->playerMoveX << endl;
				outPutFile << endl;
				outPutFile << endl;
			}
		}

	/*	for (auto & it : _scene->theFactory->g_BuildingsVector)
		{
			outPutFile << "GameObjectValue:" << it->type << endl;	
			outPutFile << "HitPoints:" << it->hitpoints << endl;
			outPutFile << "B_Gravity:" << it->m_gEffect << endl;
			outPutFile << endl;
			outPutFile << endl;
		}*/

	}
	outPutFile.close();

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

FileConfiguration::FileConfiguration(SceneBase * scene)
	:_scene(scene)
{
}

FileConfiguration::~FileConfiguration()
{

}
