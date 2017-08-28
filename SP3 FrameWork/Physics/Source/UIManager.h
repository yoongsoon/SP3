#pragma once

#include <string>
using std::string;

class SceneBase;

class UIManager
{
public:
	UIManager(SceneBase * scene);
	~UIManager();

	void UpdateText();
	void Update();
	void Render();
	void RenderText();

private:
	SceneBase * theScene;

	int a;
	double e;
	string player_weap_choice;
	string currweap_cooldown;
	string weap1_cool;
	string weap2_cool;
	string weap3_cool;
	string score_text;
	string score_counter;
	string highscore_text;
	string highscore_counter;
	string arr_highscore[5];
};