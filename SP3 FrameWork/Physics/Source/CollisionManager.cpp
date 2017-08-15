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
	// Object 1 is always assumed as GO_BALL

	if (object2->type == GameObject::GO_BALL) {
		Vector3 dist = object1->pos - object2->pos;
		Vector3 rel = object1->vel - object2->vel;
		float r1 = object1->scale.x;
		float r2 = object2->scale.x;

		return (rel.Dot(dist) < 0 && (dist).LengthSquared() <= (r1 + r2) * (r1 + r2));
	}
	else if (object2->type == GameObject::GO_WALL) {

		Vector3 w0 = object2->pos;
		Vector3 b1 = object1->pos;
		Vector3 N = object2->dir;
		Vector3 NP = N.Cross(Vector3(0, 0, 1));
		float r = object1->scale.x;
		float h = object2->scale.x;
		float l = object2->scale.y;

		Vector3 relativePos = b1 - w0;

		if (relativePos.Dot(N) > 0)
			N = -N;
		return object1->vel.Dot(N) > 0 && (abs((w0 - b1).Dot(N)) < (r + h / 2))
			&& (abs((w0 - b1).Dot(NP)) < (r + l / 2));
	}
	else if (object2->type == GameObject::GO_PILLAR) {
		Vector3 p1 = object1->pos;
		Vector3 p2 = object2->pos;
		float r1 = object1->scale.x;
		float r2 = object2->scale.x;
		Vector3 u = object1->vel;

		Vector3 dist = object1->pos - object2->pos;

		Vector3 rel = object1->vel - object2->vel;

		return (rel.Dot(dist) < 0 && (p2 - p1).LengthSquared() < (r1 + r2) * (r1 + r2))
			&& ((p2 - p1).Dot(u) > 0);
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
	else if (object2->type == GameObject::GO_WALL) {

		object1->vel = object1->vel - ((2 * object1->vel).Dot(object2->dir) *object2->dir);

	}
	else if (object2->type == GameObject::GO_PILLAR) {
		Vector3 u = object1->vel;
		Vector3 N = (object2->pos - object1->pos).Normalize();
		object1->vel = u - (2 * u.Dot(N)) * N;
	}
}

bool CollisionManager::checkProjectileCollision(Projectile * object1, GameObject * object2)
{

	//Check whether projectile(ball shape) collided with enemy ( quad shape)
	if (object2->type == GameObject::GO_ENEMY)
	{
		Vector3 w0 = object2->pos;
		Vector3 b1 = object1->pos;
		Vector3 N = object2->dir;
		Vector3 NP = N.Cross(Vector3(0, 0, 1));
		float r = object1->scale.x;
		float h = object2->scale.x;
		float l = object2->scale.y;

		Vector3 relativePos = b1 - w0;

		if (relativePos.Dot(N) > 0)
			N = -N;
		return object1->vel.Dot(N) > 0 && (abs((w0 - b1).Dot(N)) < (r + h / 2))
			&& (abs((w0 - b1).Dot(NP)) < (r + l / 2));

	}


}

void CollisionManager::projectileResponse(Projectile * object1, GameObject * object2)
{
    // projectile and enemy response
	if (object2->type == GameObject::GO_ENEMY)
	{
		//store as projectile damage as temporary variable
		float projectileDamage = object1->m_damage;
		//set the indicator to destroyed in the factory
		object1->isDestroyed = true;

		//deduct enemy hp  with projectile damage
		static_cast<Enemy*>(object2)->hp -= projectileDamage;

	}

}

void CollisionManager::Update()
{
	/*for (Mapping::iterator it = theScene->theFactory->g_FactoryMap.begin();
		it != theScene->theFactory->g_FactoryMap.end(); it++) {

		GameObject * go = (GameObject *)(it->second);

		if (go->active == false)
			continue;

		for (Mapping::iterator it2 = next(it); it2 != theScene->theFactory->g_FactoryMap.end(); it2++) {

			GameObject *go2 = static_cast<GameObject *>(it2->second);
			if (go2->active == false)
				continue;

			GameObject * goA = go;
			GameObject *goB = go2;

			if (go->type != GameObject::GO_BALL) {

				if (go2->type != GameObject::GO_BALL)
					continue;

				goA = go2;
				goB = go;
			}

			if (checkCollision(goA, goB) == true)
				collisionResponse(goA, goB);
		}
	}
*/



// double for loop to compare projectile with other games object
	for (Vectoring::iterator it = theScene->theFactory->g_ProjectileVector.begin();
		it != theScene->theFactory->g_ProjectileVector.end();
		it++) {


		if ((*it)->active == false)
			continue;

		for (Mapping::iterator it2 = theScene->theFactory->g_FactoryMap.begin();
			it2 != theScene->theFactory->g_FactoryMap.end(); it2++) {

			if (it2->second->active == false)
				continue;

			//check projectile collision with other game object
			if (checkProjectileCollision((*it), it2->second) == true) {
				projectileResponse((*it), it2->second);
			}

		}
	}
}
