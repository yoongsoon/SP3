#include "HealthBar.h"
#include "Application.h"

HealthBar::HealthBar(GAMEOBJECT_TYPE GO_ENEMY, SceneBase * scene, GameObject * go):GameObject(GO_ENEMY, scene)
{
	if (go->type == GameObject::GO_AI_CASTLE)
	{
		float m_worldHeight = 100.f;
		float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		active = true;
		meshValue = SceneBase::GEO_HEALTH_BAR;
		scale.Set(hitpoints, 1, 1);
		pos.Set(go->pos.x, go->pos.y + 5, theScene->zaxis);
	}
}

HealthBar::~HealthBar()
{

}