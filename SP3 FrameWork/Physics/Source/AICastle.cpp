#include "AICastle.h"
#include "Projectile.h"
#include "Cannon.h"
#include "Application.h"
//#include "Bow.h"
AICastle::AICastle(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
	,m_castleRange(150.f)
	,m_coolDownTime(10.f)
	,b_isAttack(false)
{
	active = true;

	meshValue = SceneBase::GEO_MINI_ENEMY_CASTLE;
	scale.Set(30, 30, 1);
	/*pos = Vector3((theScene->m_worldWidth * 3) - 15.f, 35.f, 1.f);*/
	pos = Vector3((theScene->m_worldWidth * 3) - 15.f, 33.f, 1.f);
	hitpoints = 500.f;
	m_DefaultHp = hitpoints;

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
	// update the pos when resizing the screen
	if(Application::b_isResize)
		pos = Vector3((theScene->m_worldWidth * 3) - 15.f, 35.f, 1.f);


		for (auto & it : theScene->theFactory->g_FactoryMap)
		{
			if (it.first == GameObject::GO_PLAYER)
			{
				if (it.second->active == false)
					continue;

				float distanceX = (pos.x - it.second->pos.x);

				// if hp goes below 25 %
				if (hitpoints < (m_DefaultHp * 0.25))
				{
					//shoots 3 bullets(burstfire)
					theAIweapon->Set_Max_BulletCount(3);
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

		//Destroy the castle if hp goes below 0
		if (hitpoints < 0)
		{
			hitpoints = 0;
			isDestroyed = true;
			return;
		}
}
