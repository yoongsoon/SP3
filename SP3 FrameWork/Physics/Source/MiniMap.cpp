#include "MiniMap.h"
#include "MatrixStack.h"
#include "SceneBase.h"
#include "PlayerTroops.h"

MiniMap::MiniMap(GAMEOBJECT_TYPE typeValue, SceneBase * scene)
	:GameObject(typeValue, scene)
{
	pos.Set(theScene->m_worldWidth / 2 + 12.5f, theScene->m_worldHeight - 45.f, 0.f);
	scale.Set(60.f, 10.f, 1.f);

}

MiniMap::~MiniMap()
{
}

void MiniMap::Update()
{
	float distBorderX = 60.f;

	
		for (auto & it : theScene->theFactory->g_FactoryMap)
		{
			if (it.first == GameObject::GO_ENEMY  && static_cast<Enemy*>(it.second)->StopToAttack == false)
			{
				static_cast<Enemy*>(it.second)->enemyMoveX += distBorderX / (theScene->m_worldWidth * 3 - 15.f) * (it.second->vel.x * theScene->_dt);
			}
			else if (it.first == GameObject::GO_PLAYER && static_cast<PlayerTroop*>(it.second)->StopToAttack == false)
			{
				static_cast<PlayerTroop*>(it.second)->playerMoveX += distBorderX / (theScene->m_worldWidth * 3 - 15.f) * (it.second->vel.x * theScene->_dt);
			}
		}

		arrowX = 60.f / (theScene->m_worldWidth* 3) * ( theScene->camera.position.x + 50.f);
}

void MiniMap::RenderUI()
{
	//theScene->m_worldWidth / 2 + 42.5f
	// theScene->m_worldWidth / 2 - 17.5f


	for (auto & it : theScene->theFactory->g_FactoryMap)
	{
		if (it.second->active == false)
			continue;

		if (it.first == GameObject::GO_ENEMY  )
		{
			theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_MINI_ENEMY], pos.x + 30.f + static_cast<Enemy*>(it.second)->enemyMoveX, pos.y - 2.f, scale.x - 20.f, scale.y );
		}
		else if (it.first == GameObject::GO_PLAYER )
		{
			theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_MINI_ALLIES], pos.x - 30.f + static_cast<PlayerTroop*>(it.second)->playerMoveX , pos.y - 2.f, scale.x - 20.f, scale.y);
		}
	}
	for (auto & it : theScene->theFactory->g_BuildingsVector)
	{
		if (it->active == false)
			continue;
		else if (it->type == GameObject::GO_P_CASTLE)
		{
			theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_MINI_PLAYER_CASTLE], pos.x - 37.f, pos.y, scale.x - 50.f, scale.y - 5.f);
		}
		else if (it->type == GameObject::GO_AI_CASTLE)
		{
			theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_MINI_ENEMY_CASTLE], pos.x + 37.f, pos.y, scale.x - 50.f, scale.y - 5.f);
		}
	}


	theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_MINI_ARROW], 50.f + arrowX , pos.y + 2.f, 10.f , 2.5f);
	theScene->RenderMeshOnScreen(theScene->meshList[SceneBase::GEO_MINI_BORDER], pos.x, pos.y, scale.x + 5.f, scale.y);


}

