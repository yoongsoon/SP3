#include "AICastle.h"
#include "Projectile.h"
#include "Cannon.h"

AICastle::AICastle(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
	,m_castleRange(150.f)
	,m_coolDownTime(10.f)
	,b_isAttack(false)
{
	stateOfAI = AICastle::AI_ATTACK;
	active = true;

	meshValue = SceneBase::GEO_BRICK;
	scale.Set(10, 10, 1); // prevent it from appearing
	pos = Vector3(200, 50, 0);

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

	for (auto & it : theScene->theFactory->g_FactoryMap)
	{
		if (it.first == GameObject::GO_PLAYER)
		{
		    float distanceX = (pos.x -it.second->pos.x );
						
			// starting firing projectile within castle range 
			//and the projectile motion will be "PROJECTILE_MOTION" if the
			// distance between enemy and castle is greater than 10
			if ( abs(distanceX) < m_castleRange && abs(distanceX) > 10 && it.second->active == true)
			{
				theAIweapon->castleAIDischarge(Vector3(200, 60, 0),distanceX - 50, theScene );
			}
			// change projectile motion to "LINEAR MOTION"  if the distance between
			// enemy and castle is lesser than 10
			else if (abs(distanceX) < 10 && it.second->active == true)
			{
				theAIweapon->castleAIDischarge(Vector3(200, 60, 0), it.second->pos , theScene);
			}
			else if (abs(distanceX) > m_castleRange || it.second->active == false)
			{

			}
		
		}
		

	}

	
	theAIweapon->Update(theScene->_dt);
}
