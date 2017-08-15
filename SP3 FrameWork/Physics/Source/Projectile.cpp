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
	pos.y += vel.y * theScene->_dt + ( 0.5 *  m_gravity * (theScene->_dt * theScene->_dt));
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