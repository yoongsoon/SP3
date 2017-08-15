#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

class SceneBase;

class GameObject
{
public:

	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_CUBE,
		GO_BALL,
		GO_WALL,
		GO_PILLAR,
		GO_ENEMY,
		GO_PROJECTILE,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	bool active;
	float mass;
	float rotateX;
	float rotateY;
	float rotateZ;

	unsigned meshValue;

	Vector3 m_force; // thrust force
	Vector3 dir; //direction/orientation
	float momentOfInertia;
	float angularVelocity; //in radians
	const float m_gravity; 

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	GameObject(GAMEOBJECT_TYPE typeValue, SceneBase * scene);
	virtual ~GameObject(); //<--- have to be virtual so in scenario where base class pointer poins to derived class
	                       // it will know which class's destructor to be called

	virtual void update();
	virtual void render();

     SceneBase * theScene;

	 //a bool to check whether the object should be deleted
	 bool isDestroyed;




};

#endif