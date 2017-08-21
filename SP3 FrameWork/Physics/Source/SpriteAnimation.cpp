#include "SpriteAnimation.h"
#include "MyMath.h"
#include "GL\glew.h"
#include "Vertex.h"
#include <iostream>

using std::cout;
using std::endl;

SpriteAnimation::SpriteAnimation(const std::string &meshName, int row, int col)
	: Mesh(meshName)
	, m_row(row)
	, m_col(col)
	, m_currentTime(0)
	, m_currentFrame(0)
	, m_playCount(0)
{
	m_anim = NULL;
}

SpriteAnimation::~SpriteAnimation()
{
	if (m_anim)
	{
		delete m_anim;
		m_anim = NULL;
	}
}

void SpriteAnimation::Update(double dt)
{
	if (m_anim == NULL)
		return;
	if (m_anim->animActive == false)
		return;
	if (m_anim->animActive == true) // If animation happens
	{
		m_currentTime += static_cast<float>(dt); // from 0.0 to 1.0 resets at 5th frame
		int numFrame = Math::Max(1, m_anim->endFrame - m_anim->startFrame + 1);//Number of total frames (6)
		float frameTime = m_anim->animTime / numFrame; // always 1.6667
	
		m_currentFrame = Math::Min(m_anim->endFrame, m_anim->startFrame + static_cast<int>(m_currentTime / frameTime));//current frame always 1 to 5
		//if (numFrame == 4)
		//{
		//	cout << m_currentFrame << endl;
		//}
		if (m_currentTime >= m_anim->animTime)//after all frame finish
		{
			//Reset
			if (m_anim->repeatCount == 0)// if end of all 5 frames
			{
					m_anim->animActive = false;
					m_currentTime = 0.0f;
					m_currentFrame = m_anim->startFrame;
					m_anim->ended = true;
			}
			if (m_anim->repeatCount >= 1)
			{
				m_currentTime = 0.0f;
				m_currentFrame = m_anim->startFrame;
				if (numFrame == 6)
				{
					cout << "wee" << endl;
				}
			}
		}
	}
}

void SpriteAnimation::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	//if(textureID > 0)
	//{
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	//}


	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if (m_currentFrame != dunrender)
	{
		dunrender = m_currentFrame;
		//chance = false;
	}
	if (m_currentFrame == dunrender) //&& !chance)
	{
		if (mode == DRAW_LINES)
			glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLint)));
		else if (mode == DRAW_TRIANGLE_STRIP)
			glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLint)));
		else
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLint)));
		//chance = true;
		//int numFrame = Math::Max(1, m_anim->endFrame - m_anim->startFrame + 1);
		//if (numFrame == 6)
		//{
		//	cout << "create" << m_currentFrame << endl;
		//}
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//if(textureID > 0)
	//{
	glDisableVertexAttribArray(3);
	//}
}
