#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>

using std::string;
using std::getline;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::setprecision;


#include "Vector3.h"

class SceneBase;

class FileConfiguration
{
public:
	FileConfiguration(SceneBase * scene);
	~FileConfiguration();


	//file configuration
	void loadFile(string _fileName);
	void saveFile(string _fileName);

	double Token2Double(string token);
	Vector3 Token2Vector(string token);

	SceneBase * _scene;

};