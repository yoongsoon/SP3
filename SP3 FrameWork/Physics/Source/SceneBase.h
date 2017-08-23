#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Factory.h"
#include "Enemy.h"
#include "GameObjectManager.h"
#include "Projectile.h"
#include "Buildings.h"
#include "BackGround.h"
#include "AICastle.h"
#include "MiniMap.h"
#include "PlayerTroops.h"
#include "UIManager.h"
#include "PlayerInfo.h"
#include "WeaponInfo.h"
#include "Player.h"
#include "PlayerTroops.h"

#include <vector>


class SceneBase : public Scene
{
	friend GameObject;
	friend CollisionManager;
	friend Enemy;
	friend PlayerTroop;
	friend GameObjectManager;
	friend Projectile;
	friend Buildings;
	friend BackGround;
	friend MiniMap;
	friend AICastle;
	friend UIManager;

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_CUBE,
		GEO_CIRCLE,
		GEO_SOLDIER,
		GEO_SOLDIER_ATTACK,
		GEO_ARCHER,
		GEO_ARCHER_ATTACK,
		GEO_WIZARD,
		GEO_WIZARD_ATTACK,
		GEO_BACKGROUND,
		GEO_BRICK,
		//for different projectile colours
		GEO_SPHERE1,
		GEO_SPHERE2,
		GEO_SPHERE3,

		//player weapon sprite
		GEO_P_BOW_ARROW,
		GEO_P_CANNON_BALLS,
		GEO_P_CATAPULT_ROCKS,
		//weapon display UI
		GEO_BOW_ARROW,
		GEO_CANNON_BALLS,
		GEO_CATAPULT_ROCKS,

		GEO_SPRITE_FIRE,

		GEO_TERRAIN,

		GEO_PAUSE_MENU,
		GEO_PAUSE_ARROW,
		GEO_MAIN_MENU,

		//MINIMAP 
		GEO_MINI_ARROW,
		GEO_MINI_ENEMY,
		GEO_MINI_BORDER,
		GEO_MINI_ALLIES,
		GEO_MINI_PLAYER_CASTLE,
		GEO_MINI_ENEMY_CASTLE,
		NUM_GEOMETRY,
	};

	enum SCENE_NUM
	{
		SC_START,
		SC_01,
		SC_02,
		SC_03,
		SC_04,
		SC_05,
		SC_END,
	};

	enum MENU_PAUSE
	{
		PAUSE_RESUME = 0,
		PAUSE_RESTART,
		PAUSE_MAINMENU,
	};

	MENU_PAUSE menuPause = PAUSE_RESUME;

	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	 void RenderMesh(Mesh *mesh, bool enableLight);

	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY);
	void RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY, float rotateX, float rotateY);
	//void RenderFire();

	//-------------------------------Variables---------------------------------------------------//
	float pressDelay = 0.f;
	const float cooldownPressed = 0.5f;
	float _elapsedTime = 0.f;
	float _dt = 0.f;
	float zaxis = 1.f;

	Factory * theFactory;
	MiniMap * theMiniMap;
	UIManager * theUIManager;
	PlayerInfo* thePlayer;
	Player *theplayer;

	//bool for pause
	static bool b_isPause;


	//for text
	bool weapon1 = true;
	bool weapon2 = false;
	bool weapon3 = false;

protected:
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	unsigned m_sceneID = 0;
	int m_wallStackCounter;

	Camera camera;
	MS modelStack;
	MS viewStack;
	MS projectionStack;
	Light lights[1];
	bool bLightEnabled;

	float fps;

	//--------------------------------PHYSIC CODES---------------------------------------------------//
	float m_worldWidth;
	float m_worldHeight;

	CollisionManager * theCollider;
	Enemy * theEnemy;
	GameObjectManager * gom;
	GameObject** thePredictionLine;
	GameObject * theGhostProj;
	GameObject * theReleaseMouseGhostProj;
	GameObject * theMouseGhostProj;

	double mouseX, mouseY;
	float backGroundX = 40.f;
	Mesh* meshList[NUM_GEOMETRY];

	//Terrain
	vector<unsigned char> m_heightMap;
};

#endif