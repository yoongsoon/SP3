#pragma once
#include "Vector3.h"
class GameObject;
class SceneBase;
class Projectile;

class CollisionManager
{
public:
	CollisionManager(SceneBase * _scene);
	~CollisionManager();

	//Check Collision Between Game Objects
	bool checkCollision(GameObject *object1, GameObject *object2);
	//Collision Response between Game Objects
	void collisionResponse(GameObject * object1, GameObject * object2);
	bool PointIsInBox(Vector3 point, float minX, float maxX, float minY, float maxY);
	void Update(float dt);

private:
	SceneBase * theScene;

};