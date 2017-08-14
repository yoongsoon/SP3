#include "GameObject.h"
#include "SceneBase.h"


GameObject::GameObject(GAMEOBJECT_TYPE typeValue)
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f)
	,dir(Vector3(1,0,0))
	, momentOfInertia(1.f)
	, angularVelocity(0.f)
{
}

GameObject::GameObject(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	rotateX(0),
	rotateY(0),
	rotateZ(0),
	meshValue(0),
	theScene(scene)
	,m_force(Vector3(0,0,0))
	, dir(Vector3(1, 0, 0))
	, momentOfInertia(1.f)
	, angularVelocity(0.f)
{

}

GameObject::~GameObject()
{

}

void GameObject::update()
{

}

void GameObject::render()
{
	theScene->modelStack.PushMatrix();
	theScene->modelStack.Translate(pos.x, pos.y, pos.z);
	theScene->modelStack.Rotate(rotateX, 1, 0, 0);
	theScene->modelStack.Rotate(rotateY, 0, 1, 0);
	theScene->modelStack.Rotate(rotateZ, 0, 0, 1);
	theScene->modelStack.Scale(scale.x, scale.y, scale.z);
	theScene->RenderMesh(theScene->meshList[meshValue], false);
	theScene->modelStack.PopMatrix();

}
