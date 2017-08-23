#include "FileConfiguration.h"
#include "SceneBase.h"
#include "Enemy.h"
#include "PlayerTroops.h"
#include "Buildings.h"

void FileConfiguration::loadFile(string _fileName)
{
	ifstream myLoadFile;
	string eachLine;
	unsigned  tempType;
	Vector3 tempPos;


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

				// copy contents of ss into aToken until '=' is reached
				while (getline(ss, aToken, ':'))
				{
					string theTag = aToken;
					getline(ss, aToken, ':');

					if (theTag == "")
					{

					}
				}
			}
		}
	}
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
		for (auto & it : _scene->theFactory->g_FactoryMap)
		{
			if (it.second->active == false)
				continue;

			if (it.first == GameObject::GO_ENEMY)
			{
				outPutFile <<"Enemy Type:"<< static_cast<Enemy*>(it.second)->enemyType << endl;
				outPutFile <<"Position:"<< it.second->pos << endl;
				outPutFile <<"Hp:"<< static_cast<Enemy*>(it.second)->hp << endl;
				outPutFile <<"StopAttack:"<< static_cast<Enemy*>(it.second)->StopToAttack << endl;
				outPutFile << "Timer:"<<static_cast<Enemy*>(it.second)->timer << endl;
				outPutFile << "Attacked:"<<static_cast<Enemy*>(it.second)->Attacked << endl;
				outPutFile << endl;
				outPutFile << endl;
			}
			else if (it.first == GameObject::GO_PLAYER)
			{
				outPutFile <<"Player Type:"<<static_cast<PlayerTroop*>(it.second)->playerType << endl;
				outPutFile << "Position:" << it.second->pos << endl;
				outPutFile << "Hp:"<<static_cast<PlayerTroop*>(it.second)->hp << endl;
				outPutFile << "StopAttack:" << static_cast<PlayerTroop*>(it.second)->StopToAttack << endl;
				outPutFile <<"Timer:"<<static_cast<PlayerTroop*>(it.second)->timer << endl;
				outPutFile << "Attacked:" << static_cast<PlayerTroop*>(it.second)->Attacked << endl;
				outPutFile << endl;
				outPutFile << endl;
			}
			else if (it.first == GameObject::GO_CASTLE)
			{
				if (it.second->type == )
				{

				}
			}

		}

	}
	outPutFile.close();

}

Vector3 FileConfiguration::Token2Vector(string token)
{
	Vector3 tempVector(0.0f, 0.0f, 0.0f);

	istringstream ss(token);
	string aToken = "";
	getline(ss, aToken, ',');
	tempVector.x = stof(aToken);
	getline(ss, aToken, ',');
	tempVector.y = stof(aToken);
	getline(ss, aToken, ',');
	tempVector.z = stof(aToken);

	return tempVector;
}

FileConfiguration::FileConfiguration()
{
}

FileConfiguration::~FileConfiguration()
{
}
