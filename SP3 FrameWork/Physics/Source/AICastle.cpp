#include "AICastle.h"
#include "Projectile.h"
#include "Cannon.h"
//#include "Bow.h"
AICastle::AICastle(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
	,m_castleRange(150.f)
	,m_coolDownTime(10.f)
	,b_isAttack(false)
{
	stateOfAI = AICastle::AI_ATTACK;
	active = true;
	m_DefaultHp = m_hp;

	meshValue = SceneBase::GEO_MINI_ENEMY_CASTLE;
	scale.Set(30, 30, 1); 
	pos = Vector3( (theScene->m_worldWidth * 3)- 15.f , 50.f, 1.f);

	theAIweapon = new Cannon();
	theAIweapon->Init();
	//AIweapons = new Weapon_Info*[totanumberAIweapons];
	//int totanumberAIweapons;
	//int currAIweapon
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

		for (auto & it : theScene->theFactory->g_FactoryMap)
		{
			if (it.first == GameObject::GO_PLAYER)
			{
				if (it.second->active == false)
					continue;

				float distanceX = (pos.x - it.second->pos.x);
				it.second->pos.z = 5;
				// if hp goes below 25 %
				if (m_hp < (m_DefaultHp * 0.25))
				{
					//shoots 3 bullets(burstfire)
					theAIweapon->Set_Max_BulletCount(3);
					//theAIweapon->setFireMode(Weapon_Info::BURST_FIRE);
				}
				else
				{
					//shoot 1 bullet(burstfire) == no burstfire
					theAIweapon->Set_Max_BulletCount(1);
				}

				// starting firing projectile within castle range 
				//and the projectile motion will be "PROJECTILE_MOTION" if the
				// distance between enemy and castle is greater than 10
				if (abs(distanceX) < m_castleRange && abs(distanceX) > 10 )
				{
					theAIweapon->castleAIDischarge(Vector3(pos.x, 60, 5), distanceX - 50, theScene);
				}
				// change projectile motion to "LINEAR MOTION"  if the distance between
				// enemy and castle is lesser than 10
				else if (abs(distanceX) < 10 )
				{
					theAIweapon->castleAIDischarge(Vector3(pos.x, 60, 5), it.second->pos, theScene);
				}
			}
		}
		theAIweapon->Update(theScene->_dt);
}
