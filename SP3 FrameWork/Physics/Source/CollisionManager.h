#pragma once

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

	//Check Collision Between Projectile and other game objects
	bool checkProjectileCollision(Projectile *object1, GameObject *object2);
	void projectileResponse(Projectile *object1, GameObject *object2);

	void Update();

private:
	SceneBase * theScene;

};