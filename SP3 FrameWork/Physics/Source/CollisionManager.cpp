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
	Vector3 obj2Right = obj2Normal.Cross(Vector3(0, 0, 1));
	// Get vector to object1 from object2
	Vector3 Pos1ToPos2 = obj1pos - obj2pos;
	// Get vector to object2 from object1
	Vector3 Pos2ToPos1 = obj2pos - obj1pos;
	Vector3 selfToTargetDirection;
	Vector3 radialPosToTarget;
	Vector3 relativeVel = object1->vel - object2->vel;
	float rotateAngle;

	if (object1->type == GameObject::GO_PROJECTILE)
	{
		switch (object2->type)
		{
			// obj2 = ball
		/*case GameObject::GO_PROJECTILE:
			return (relativeVel.Dot(relativePos1) < 0 && (relativePos1).LengthSquared() <= (obj1scale.x + obj2scale.x) * (obj1scale.x + obj2scale.x));
			break;*/
			// obj2 = wall
		//case GameObject::GO_ENEMY:
		case GameObject::GO_PLAYER:
		case GameObject::GO_BRICK:
			//rotateAngle = 

			object2->topLeft.Set(obj2pos.x - (obj2scale.x * 0.5f), obj2pos.y + (obj2scale.y * 0.5f), 0);
			object2->topRight.Set(obj2pos.x + (obj2scale.x * 0.5f), obj2pos.y + (obj2scale.y * 0.5f), 0);
			object2->bottomLeft.Set(obj2pos.x - (obj2scale.x * 0.5f), obj2pos.y - (obj2scale.y * 0.5f), 0);
			object2->bottomRight.Set(obj2pos.x + (obj2scale.x * 0.5f), obj2pos.y - (obj2scale.y * 0.5f), 0);
			//cout << obj2Normal << endl;
			// Check if object1 is relatively close to object2 in terms of Y-axis
			if (obj1pos.y <= object2->topLeft.y && obj1pos.y >= object2->bottomRight.y)
			{
				if (obj1pos.x > obj2pos.x)
					selfToTargetDirection.Set(-1, 0, 0);
				else
					selfToTargetDirection.Set(1, 0, 0);
			}
			// Check if object1 is relatively close to object2 in terms of X-axis
			else if (obj1pos.x >= object2->topLeft.x && obj1pos.x <= object2->bottomRight.x)
			{
				if (obj1pos.y > obj2pos.y)
					selfToTargetDirection.Set(0, -1, 0);
				else
					selfToTargetDirection.Set(0, 1, 0);
			}
			else
			{
				if (obj1pos.y > object2->topLeft.y)
				{
					if (obj1pos.x < object2->topLeft.x)
						selfToTargetDirection = object2->topLeft - obj1pos;
					else
						selfToTargetDirection = object2->topRight - obj1pos;
				}
				else if (obj1pos.y < object2->bottomRight.y)
				{
					if (obj1pos.x < object2->bottomLeft.x)
						selfToTargetDirection = object2->bottomLeft - obj1pos;
					else
						selfToTargetDirection = object2->bottomRight - obj1pos;
				}
				selfToTargetDirection.Normalize();
			}

			radialPosToTarget = obj1pos + (selfToTargetDirection * obj1scale.x);

			if (Pos1ToPos2.Dot(obj2Normal) > 0)
				obj2Normal = -obj2Normal;
			if (Pos1ToPos2.Dot(obj2Right) > 0)
				obj2Right = -obj2Right;


			if (object1->vel.Dot(obj2Normal) > 0 || object1->vel.Dot(obj2Right) > 0)
			{
				return (radialPosToTarget.x >= object2->topLeft.x && radialPosToTarget.y <= object2->topLeft.y
					&& radialPosToTarget.x <= object2->topRight.x && radialPosToTarget.y <= object2->topRight.y
					&& radialPosToTarget.x >= object2->bottomLeft.x && radialPosToTarget.y >= object2->bottomLeft.y
					&& radialPosToTarget.x <= object2->bottomRight.x && radialPosToTarget.y >= object2->bottomRight.y);
			}
		}
	}
			// testing
		

		//	//	
		//}
		//return false;

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
	return false;
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
		object1->vel *= -1;
		//object1->vel = object1->vel - ((2 * object1->vel).Dot(object2->dir) *object2->dir);
	}
	else if (object2->type == GameObject::GO_PILLAR) {
		Vector3 u = object1->vel;
		Vector3 N = (object2->pos - object1->pos).Normalize();
		object1->vel = u - (2 * u.Dot(N)) * N;
	}
	//PLAYER PROJECTILE DAMAGE TO ENEMY TROOPS
	else if (static_cast<Projectile*>(object1)->whoseProjectile == Projectile::PROJECTILE_WHOSE::PLAYER_PROJECTILE && object2->type == GameObject::GO_ENEMY)
	{
		//store as projectile damage as temporary variable
		float projectileDamage = static_cast<Projectile*>(object1)->m_damage;
		object1->active = false;

		//deduct enemy hp  with projectile damage
		static_cast<Enemy*>(object2)->hp -= projectileDamage;

	}
	// AI CASTLE PROJECTILE DAMAGE TO PLAYER TROOPS
	else if (static_cast<Projectile*>(object1)->whoseProjectile == Projectile::PROJECTILE_WHOSE::ENEMY_PROJECTILE && object2->type == GameObject::GO_PLAYER)
	{
		float projectileDamage = static_cast<Projectile*>(object1)->m_damage;
		object1->active = false;

		static_cast<PlayerTroop*>(object2)->hp -= projectileDamage;
	}
	
}


void CollisionManager::Update(float dt)
{
// double for loop to compare projectile with other games object
	for (Vectoring::iterator it = theScene->theFactory->g_ProjectileVector.begin(); it != theScene->theFactory->g_ProjectileVector.end();it++) 
	{
		
		if ((*it)->active == false)
			continue;

		for (Mapping::iterator it2 = theScene->theFactory->g_FactoryMap.begin();
			it2 != theScene->theFactory->g_FactoryMap.end(); it2++) 
		{

			if (it2->second->active == false)
				continue;

			GameObject* goA = (*it);
			GameObject* goB = it2->second;

			//check projectile collision with other game object
			if ((*it)->type != GameObject::GO_PROJECTILE)
			{
				if (it2->second->type != GameObject::GO_PROJECTILE)
					continue;
				goA = it2->second;
				goB = (*it);
			}

			if (checkCollision(goA, goB)) 
			{
				collisionResponse(goA, goB);
			}

		}
	}
}
