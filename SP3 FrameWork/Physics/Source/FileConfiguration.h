#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using std::string;
using std::getline;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;

#include "Vector3.h"
#include "Singleton.h"

class SceneBase;

class FileConfiguration : public Singleton<FileConfiguration>
{
	friend Singleton<FileConfiguration>;
public:
	//file configuration
	void loadFile(string _fileName);
	void saveFile(string _fileName);

	Vector3 Token2Vector(string token);

protected:
	FileConfiguration();
	~FileConfiguration();

	SceneBase * _scene;

};