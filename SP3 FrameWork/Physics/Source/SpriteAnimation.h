#pragma once
#include <iostream>
#include "Mesh.h"
//#include "Vector2.h"
using std::string;

struct Animation
{
	Animation() {}
	void Set(int _startFrame, int _endFrame, int _repeat, float _time, bool _active)
	{
		this->startFrame = _startFrame;
		this->endFrame = _endFrame;
		this->repeatCount = _repeat;
		this->animTime = _time;
		this->animActive = _active;
	}
	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;
	bool animActive;
};

class SpriteAnimation : public Mesh 
{
public:
	SpriteAnimation(const std::string &meshName, int row, int col);
	~SpriteAnimation();
	void Update(double dt);
	virtual void Render();
	int m_row;
	int m_col;
	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;
};