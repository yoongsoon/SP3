#include "Projectile.h"
#include "SceneBase.h"

Projectile::Projectile(PROJECTILE_TYPE _typeofProjectile, GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
	, m_launchAngle(30.f)
	, MAX_SPEED(15.f)
{
	meshValue = SceneBase::GEO_CIRCLE;
	typeOfProjectile = _typeofProjectile;

	switch (typeOfProjectile)
	{
	case ARROW_PROJECTILE:
	{
		m_damage = 1.f;
	}
	break;
	case ROCK_PROJECTILE:
	{
		m_damage = 5.f;
	}
	break;
	case CANNON_BALL_PROJECTILE:
	{
		m_damage = 10.f;
	}
	break;
	}

	
	vel.x = vel.Length() * cos(Math::RadianToDegree(m_launchAngle));
	vel.y = vel.Length() * sin(Math::RadianToDegree(m_launchAngle));

}

Projectile::~Projectile()
{
}

void Projectile::setInitVel(float _range)
{
	// s= v^2 sin20 /g
	 // v = sqrt ( s  / sin20/g)

	 // range = velX * time
	 // time = 2 * vel  * sin 0 / g
	 // velx  = vel * cos0

	vel = sqrt(_range * -m_gravity) / (2 * sin(Math::RadianToDegree(m_launchAngle) * cos(Math::RadianToDegree(m_launchAngle))));


	
	vel.x = vel.Length() * cos(Math::RadianToDegree(m_launchAngle));
	vel.y = vel.Length() * sin(Math::RadianToDegree(m_launchAngle));

}

void Projectile::update()
{
	if (m_gEffect)
		vel.y += m_gravity *theScene->_dt;

	pos.x += vel.x * theScene->_dt;
	pos.y += vel.y * theScene->_dt + (0.5f *  m_gravity * (theScene->_dt * theScene->_dt));

	// delete projectile when it goes out of range
	if (pos.x < 0.f)
	{
		isDestroyed = true;
		return;
	}
	else if (pos.x > theScene->m_worldWidth * 2)
	{
		isDestroyed = true;
		return;
	}
	else if (pos.y < 0.f)
	{
		isDestroyed = true;
		return;
	}
}

//
//Projectile* Create::Projectile(const std::string& _meshName,
//	const Vector3& _position,
//	const Vector3& _direction,
//	const float m_fLifetime,
//	const float m_fSpeed,
//	Projectile* _source)
//{
//	Mesh* modelMesh = MeshBuilder::GetInstance()->GetMesh(_meshName);
//	if (modelMesh == nullptr)
//		return nullptr;
//
//	Projectile* result = new Projectile(modelMesh);
//	result->Set(_position, _direction, m_fLifetime, m_fSpeed);
//	result->SetStatus(true);
//	result->SetCollider(true);
//	result->SetSource(_source);
//	EntityManager::GetInstance()->AddEntity(result);
//
//	return result;
//}

Projectile * Create::createProjectile(Projectile::PROJECTILE_TYPE _typeofProjectile, GameObject::GAMEOBJECT_TYPE typevalue, SceneBase * scene)
{
	// initialse projectile pointer
	Projectile * theProjectile = new Projectile(_typeofProjectile, typevalue, scene);
	// push the projectile pointer into the factory
	theProjectile->theScene->theFactory->createGameObject(theProjectile);

	// return the projectile pointer so it can be use in other classes to set the projectile pos ,sclae and etc
	return theProjectile;
}
