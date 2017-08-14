#pragma once

class SceneBase;
class GameObject;

class GameObjectManager
{
public:
	
	GameObjectManager(SceneBase * scene);
	~GameObjectManager();




private:
	SceneBase * _scene;

	

};