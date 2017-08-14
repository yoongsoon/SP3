#include "GameObjectManager.h"
#include "GameObject.h"
#include "SceneBase.h"

GameObjectManager::GameObjectManager(SceneBase * scene)
	:_scene(scene)

{

}

GameObjectManager::~GameObjectManager()
{
	if (_scene)
	{
		delete _scene;
		_scene = NULL;
	}


}
