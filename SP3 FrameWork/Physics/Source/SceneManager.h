#pragma once

#include "Singleton.h"

#include <string>
#include <map>

using std::string;
using std::map;

class SceneBase; // Foward delcaration

class SceneManager :public Singleton<SceneManager>
{
	friend Singleton<SceneManager>; // declare singleton class as friend so singleton class can access private variables
	                               // of  constructor SceneManager to create an instance in singleton of type SceneManager
public:
	//System Interface
	void Update(double _dt);
	void Render();
	void Exit();

	//User Interface
	void AddScene(const string& _name, SceneBase* _scene);
	void RemoveScene(const string& _name);
	void SetActiveScene(const string& _name);
	bool CheckSceneExist(const string& _name);


private:
	SceneManager();
	~SceneManager();

	SceneBase * activeScene;
	SceneBase * nextScene;

	map<string, SceneBase * > sceneMap;
};