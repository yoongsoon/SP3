#include "Projectile.h"
#include "SceneBase.h"

Projectile::Projectile(PROJECTILE_TYPE _typeofProjectile, GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
	, m_launchAngle(30.f)
	, MAX_SPEED(15.f)
	,speed (50.f)
{
	meshValue = SceneBase::GEO_CIRCLE;
	typeOfProjectile = _typeofProjectile;
  
	switch (typeOfProjectile)
	{
	case ARROW_PROJECTILE:
	{
		meshValue = SceneBase::GEO_SPHERE1;
		m_damage = 10.f;
	}
	break;
	case ROCK_PROJECTILE:
	{
		meshValue = SceneBase::GEO_SPHERE2;
		m_damage = 20.f;
	}
	break;
	case CANNON_BALL_PROJECTILE:
	{
		meshValue = SceneBase::GEO_SPHERE3;
		m_damage = 30.f;
	}
	break;
	case GHOST_PROJECTILE:
	{
		meshValue = SceneBase::GEO_CIRCLE;
		m_damage = 0;
		m_gravity = 0;
	}
	break;
	}


	/*vel.x = speed * cos(Math::RadianToDegree(m_launchAngle));
	vel.y = speed * sin(Math::RadianToDegree(m_launchAngle));*/

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

	m_launchAngle = 220;

	vel = sqrt(_range * m_gravity) / (2 * sin(Math::DegreeToRadian(m_launchAngle) * cos(Math::DegreeToRadian(m_launchAngle))));

	// to check if square root gives any invalid value , if is does negate the sign for m_gravity
	if (std::isnan(vel.x) || std::isnan(vel.y) ||std::isnan(vel.z) )
		vel = sqrt(_range * -m_gravity) / (2 * sin(Math::DegreeToRadian(m_launchAngle) * cos(Math::DegreeToRadian(m_launchAngle))));


	//vel.x = speed * cos(Math::DegreeToRadian(m_launchAngle));
	//vel.y = speed * sin(Math::DegreeToRadian(m_launchAngle));

}

void Projectile::update()
{
	switch (typeOfMotion)
	{
	case PROJECTILE_MOTION:
	{
		if (m_gEffect)
			vel.y += m_gravity *theScene->_dt;

		pos += vel * theScene->_dt;
	}
	break;
	case LINEAR_MOTION:
	{
		pos += vel * theScene->_dt;
	}
	break;
	}

	
	// delete projectile when it goes out of range
	if (pos.x < 0.f)
	{
		isDestroyed = true;
		return;
	}
	else if (pos.x > theScene->m_worldWidth * 3)
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
