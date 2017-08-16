#include "AICastle.h"
#include "Projectile.h"
#include "WeaponInfo.h"
#include "Cannon.h"

AICastle::AICastle(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
	,m_castleRange(40.f)
	,m_coolDownTime(10.f)
	,b_isAttack(false)
{
	stateOfAI = AICastle::AI_ATTACK;
	active = true;

	meshValue = SceneBase::GEO_BRICK;
	pos = Vector3(50, 50, 0);

	theAIweapon = new Cannon();
	theAIweapon->Init();

}

AICastle::~AICastle()
{
}

void AICastle::update()
{
	switch (stateOfAI)
	{
	case AI_IDLE:
	{

	}
	break;
	case AI_ATTACK:
	{
		

	}
	break;
	}

	theAIweapon->Discharge(Vector3(200, 60, 0), 5.f, theScene);
	theAIweapon->Update(theScene->_dt);
}
