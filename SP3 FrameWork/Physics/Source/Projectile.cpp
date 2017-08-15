#include "Projectile.h"
#include "SceneBase.h"

Projectile::Projectile(PROJECTILE_TYPE _typeofProjectile, GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue , scene)
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

void Projectile::update()
{
	if (m_gEffect)
		vel.y += m_gravity *theScene->_dt;

	pos.x +=  vel.x * theScene->_dt;
	pos.y += vel.y * theScene->_dt + ( 0.5f *  m_gravity * (theScene->_dt * theScene->_dt));
}
