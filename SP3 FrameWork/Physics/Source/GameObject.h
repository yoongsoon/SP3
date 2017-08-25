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
		GO_PLAYER,
		GO_P_PROJECTILE,
		GO_AI_PROJECTILE,
		GO_P_BRICK,
		GO_AI_BRICK,
		GO_P_CASTLE,
		GO_MINI_P_CASTLE,
		GO_FIRE,
		GO_AI_CASTLE,
		GO_MINI_MAP,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 topLeft, topRight, bottomLeft, bottomRight;
	Vector3 wallPos;
	bool m_canFall;
	bool active;
	bool m_gEffect;

	std::string debugTag = "";

	float mass;
	float rotateX;
	float rotateY;
	float rotateZ; 
	int hitpoints;
	unsigned meshValue;

	Vector3 m_force; // thrust force
	Vector3 dir; //direction/orientation
	float momentOfInertia;
	float angularVelocity; //in radians
	float m_gravity; 
	
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