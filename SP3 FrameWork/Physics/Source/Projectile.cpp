#include "Projectile.h"
#include "SceneBase.h"

Projectile::Projectile(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue , scene)
	, m_launchAngle(30.f)
	, MAX_SPEED(15.f)
{
	meshValue = SceneBase::GEO_CIRCLE;

	vel.x = vel.Length() * cos(Math::RadianToDegree(m_launchAngle));
	vel.y = vel.Length() * sin(Math::RadianToDegree(m_launchAngle));
}

Projectile::~Projectile()
{
}

void Projectile::update()
{
	vel.y += m_gravity *theScene->_dt;

	pos.x +=  vel.x * theScene->_dt;
	pos.y += vel.y * theScene->_dt + ( 0.5f *  m_gravity * (theScene->_dt * theScene->_dt));
}
