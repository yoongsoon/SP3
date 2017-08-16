#pragma once

class SceneBase;
class GameObject;
class CollisionManager;

class GameObjectManager
{
public:
	
	GameObjectManager(SceneBase * scene);
	~GameObjectManager();

	void update();
	
	CollisionManager * collider;
	void Enemy_Enemy_Collision();
private:
	SceneBase * theScene;

	

};