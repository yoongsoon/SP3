#include "CollisionManager.h"
#include "GameObject.h"
#include "Factory.h"
#include "SceneBase.h"
#include "Projectile.h"
#include "Enemy.h"

using std::next;

CollisionManager::CollisionManager(SceneBase * _scene)
	:theScene(_scene)
{
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::checkCollision(GameObject * object1, GameObject * object2)
{
	Vector3 obj1pos = object1->pos;
	Vector3 obj2pos = object2->pos;
	Vector3 obj1scale = object1->scale;
	Vector3 obj2scale = object2->scale;
	Vector3 obj2Normal = object2->dir;
	Vector3 obj2NormalP = obj2Normal.Cross(Vector3(0, 0, 1));
	Vector3 relativePos = obj1pos - obj2pos;
	Vector3 relativeVel = object1->vel - object2->vel;

	switch (object1->type)
	{
		// obj1 = ball
	case GameObject::GO_PROJECTILE:
		switch (object2->type)
		{
			// obj2 = ball
		case GameObject::GO_PROJECTILE:
			return (relativeVel.Dot(relativePos) < 0 && (relativePos).LengthSquared() <= (obj1scale.x + obj2scale.x) * (obj1scale.x + obj2scale.x));
			break;
			// obj2 = wall
		case GameObject::GO_BRICK:
			if (relativePos.Dot(obj2Normal) > 0)
				obj2Normal = -obj2Normal;
			return object1->vel.Dot(obj2Normal) > 0 && (abs((obj2pos - obj1pos).Dot(obj2Normal)) < (obj1scale.x + obj2scale.x / 2))
				&& (abs((obj2pos - obj1pos).Dot(obj2NormalP)) < (obj1scale.x + obj2scale.y / 2));
			break;
		default:
			cout << "Nothing to compare to!" << endl;
			break;
		}
		return false;
		break;
		
		/*else if (object2->type == GameObject::GO_PILLAR) {
			Vector3 p1 = object1->pos;
			Vector3 p2 = object2->pos;
			float r1 = object1->scale.x;
			float r2 = object2->scale.x;
			Vector3 u = object1->vel;

			Vector3 dist = object1->pos - object2->pos;

			Vector3 rel = object1->vel - object2->vel;

			return (rel.Dot(dist) < 0 && (p2 - p1).LengthSquared() < (r1 + r2) * (r1 + r2))
				&& ((p2 - p1).Dot(u) > 0);*/
	}
	
}

void CollisionManager::collisionResponse(GameObject * object1, GameObject * object2)
{
	if (object2->type == GameObject::GO_BALL) {
		float m1 = object1->mass;
		float m2 = object2->mass;
		Vector3 u1 = object1->vel;
		Vector3 u2 = object2->vel;
		Vector3 N;
		try
		{
			N = (object2->pos - object1->pos).Normalize();
		}
		catch (DivideByZero e)
		{

		}
		Vector3 u1Normal = u1.Dot(N) * N;
		Vector3 u2Normal = u2.Dot(N) * N;

		object1->vel = u1 + (2 * m2 / (m1 + m2)) * (u2Normal - u1Normal);
		object2->vel = u2 + (2 * m1 / (m1 + m2)) * (u1Normal - u2Normal);
	}
	else if (object2->type == GameObject::GO_BRICK)
	{
		object1->vel = object1->vel - ((2 * object1->vel).Dot(object2->dir) *object2->dir);
	}
	else if (object2->type == GameObject::GO_PILLAR) {
		Vector3 u = object1->vel;
		Vector3 N = (object2->pos - object1->pos).Normalize();
		object1->vel = u - (2 * u.Dot(N)) * N;
	}
	else if (object2->type == GameObject::GO_ENEMY)
	{
		//store as projectile damage as temporary variable
		float projectileDamage = static_cast<Projectile*>(object1)->m_damage;
		//set the indicator to destroyed in the factory
		object1->isDestroyed = true;

		//deduct enemy hp  with projectile damage
		static_cast<Enemy*>(object2)->hp -= projectileDamage;

	}
}


void CollisionManager::Update(float dt)
{
// double for loop to compare projectile with other games object
	for (Vectoring::iterator it = theScene->theFactory->g_ProjectileVector.begin();
		it != theScene->theFactory->g_ProjectileVector.end();
		it++) 
	{


		if ((*it)->active == false)
			continue;

		for (Mapping::iterator it2 = theScene->theFactory->g_FactoryMap.begin();
			it2 != theScene->theFactory->g_FactoryMap.end(); it2++) 
		{

			if (it2->second->active == false)
				continue;

			//check projectile collision with other game object
			if (checkCollision((*it), it2->second) == true) 
			{
				collisionResponse((*it), it2->second);
			}

		}
	}
}
