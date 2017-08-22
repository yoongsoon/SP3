#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Application.h"
#include "Utility.h"
#include <sstream>
#include "MeshBuilder.h"
#include "LoadTGA.h"

bool SceneBase::b_isPause = false;

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//m_programID = LoadShaders("Shader//comg.vertexshader", "Shader//comg.fragmentshader");
	m_programID = LoadShaders("Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");

	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_NUMLIGHTS], 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 2.f);
	meshList[GEO_CIRCLE] = MeshBuilder::GenerateSphere("circle", Color(1, 0, 0), 10, 10, 1.f);
	meshList[GEO_SPHERE1] = MeshBuilder::GenerateSphere("sphere1", Color(1, 1, 0), 10, 10, 1.f);
	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("sphere2", Color(0, 1, 1), 10, 10, 1.f);
	meshList[GEO_SPHERE3] = MeshBuilder::GenerateSphere("sphere3", Color(1, 0, 1), 10, 10, 1.f);

	//Player weapon Sprite
	meshList[GEO_P_BOW_ARROW] = MeshBuilder::GenerateSpriteAnimation("P_bow_arrow",2,6, 1.0f);
	meshList[GEO_P_BOW_ARROW]->textureID = LoadTGA("Image//P_Bow_and_Arrows_SPRITE.tga");
	meshList[GEO_P_CANNON_BALLS] = MeshBuilder::GenerateSpriteAnimation("P_cannon_balls", 2,6, 1.f);
	meshList[GEO_P_CANNON_BALLS]->textureID = LoadTGA("Image//P_Bow_and_Arrows_SPRITE.tga");
	meshList[GEO_P_CATAPULT_ROCKS] = MeshBuilder::GenerateSpriteAnimation("P_catapult_rocks", 2,5, 1.f);
	meshList[GEO_P_CATAPULT_ROCKS]->textureID = LoadTGA("Image//P_Catapult_Rocks_SPRITE.tga");

	//Displays
	meshList[GEO_BOW_ARROW] = MeshBuilder::GenerateQuad("dis_bow_arrow", Color(1, 1, 1),1.f);
	meshList[GEO_BOW_ARROW]->textureID = LoadTGA("Image//d_Bow_and_Arrows.tga");
	meshList[GEO_CANNON_BALLS] = MeshBuilder::GenerateQuad("dis_Cannon_balls", Color(1, 1, 1), 1.f);
	meshList[GEO_CANNON_BALLS]->textureID = LoadTGA("Image//d_Cannon_balls.tga");
	meshList[GEO_CATAPULT_ROCKS] = MeshBuilder::GenerateQuad("dis_Catapult_Rocks", Color(1, 1, 1), 1.f);
	meshList[GEO_CATAPULT_ROCKS]->textureID = LoadTGA("Image//d_Catapult_Rocks.tga");
	//-----
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//ExportedFont2.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_BRICK] = MeshBuilder::GenerateCube("brick", Color(.5f, .5f, .5f), 1.f);
	//meshList[GEO_BRICK]->textureID = LoadTGA("Image//castlebrick.tga");
	meshList[GEO_SOLDIER] = MeshBuilder::GenerateSpriteAnimation("soldier", 2, 3, 1.0f);
	meshList[GEO_SOLDIER]->textureID = LoadTGA("Image//SoldierWalking.tga");
	meshList[GEO_ARCHER] = MeshBuilder::GenerateSpriteAnimation("archer", 1, 4, 1.0f);
	meshList[GEO_ARCHER]->textureID = LoadTGA("Image//ArcherWalking.tga");
	meshList[GEO_WIZARD] = MeshBuilder::GenerateSpriteAnimation("wizard", 4, 4, 1.0f);
	meshList[GEO_WIZARD]->textureID = LoadTGA("Image//fire.tga");
	meshList[GEO_BRICK] = MeshBuilder::GenerateQuad("brick", Color(.5f, .5f, .5f), 1.f);
	meshList[GEO_BRICK]->textureID = LoadTGA("Image//castlebrick.tga");
	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateQuad("BackGround", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image/BackGround.tga");
	meshList[GEO_PAUSE_MENU] = MeshBuilder::GenerateQuad("PauseMenu", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_PAUSE_MENU]->textureID = LoadTGA("Image/PauseMenu.tga");
	meshList[GEO_PAUSE_ARROW] = MeshBuilder::GenerateQuad("PauseArrow", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_PAUSE_ARROW]->textureID = LoadTGA("Image/PauseArrow.tga");

	//--------------------Main Menu--------------------------//
	meshList[GEO_MAIN_MENU] = MeshBuilder::GenerateQuad("MainMenu", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MAIN_MENU]->textureID = LoadTGA("Image/menu.tga");


	//-------------------Terrain-------------------------------//
	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("GEO_TERRAIN",
		"Image//heightmap.raw", m_heightMap);
	meshList[GEO_TERRAIN]->textureID = LoadTGA("Image//castlebrick.tga");

	//-------------------------------MINIMAP-------------------------------------//
	meshList[GEO_MINI_ARROW] = MeshBuilder::GenerateQuad("miniArrow", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MINI_ARROW]->textureID = LoadTGA("Image/miniArrow.tga");
	meshList[GEO_MINI_BORDER] = MeshBuilder::GenerateQuad("miniBorder", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MINI_BORDER]->textureID = LoadTGA("Image/mini_border.tga");
	meshList[GEO_MINI_ENEMY] = MeshBuilder::GenerateQuad("miniEnemy", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MINI_ENEMY]->textureID = LoadTGA("Image/mini_enemy.tga");
	meshList[GEO_MINI_ALLIES] = MeshBuilder::GenerateQuad("miniallies", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MINI_ALLIES]->textureID = LoadTGA("Image/mini_allies.tga");
	meshList[GEO_MINI_PLAYER_CASTLE] = MeshBuilder::GenerateQuad("mini_playercastle", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MINI_PLAYER_CASTLE]->textureID = LoadTGA("Image/miniPlayerCastle.tga");
	meshList[GEO_MINI_ENEMY_CASTLE] = MeshBuilder::GenerateQuad("mini_enemy_castle", Color(1.f, 1.f, 1.f), 1.f);
	meshList[GEO_MINI_ENEMY_CASTLE]->textureID = LoadTGA("Image/miniEnemyCastle.tga");

	bLightEnabled = false;
}

void SceneBase::Update(double dt)
{
	//Keyboard Section
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	fps = (float)(1.f / dt);

}

//void SceneBase::RenderFire()
//{
//	m_worldHeight = 100.f;
//	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
//
//	modelStack.PushMatrix();
//
//	Vector3 pos;
//	pos.x = m_worldWidth / 2;
//	pos.z = 0.f;
//
//	pos.y = m_worldHeight / 2;
//
//	modelStack.Translate(pos.x, pos.y, pos.z);
//	modelStack.Scale(10, 10, 10);
//	RenderMesh(meshList[GEO_SPRITE_FIRE], false);
//	modelStack.PopMatrix();
//}


void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneBase::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 160, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode

	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate((float)x, (float)y, 0);
	modelStack.Scale((float)sizeX, (float)sizeY, 1);
	//to do: scale and translate accordingly
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}


void SceneBase::RenderMeshOnScreen(Mesh* mesh, float x, float y, float sizeX, float sizeY, float rotateX, float rotateY)
{
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode

	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate((float)x, (float)y, 0);
	modelStack.Rotate(rotateX, 1, 0, 0);
	modelStack.Rotate(rotateY, 0, 1, 0);
	modelStack.Scale((float)sizeX, (float)sizeY, 1);
	//to do: scale and translate accordingly
	RenderMesh(mesh, false); //UI should not have light
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}


void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void SceneBase::Exit()
{
	// Cleanup VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
