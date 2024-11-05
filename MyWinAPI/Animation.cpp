#include "pch.h"
#include "Animation.h"

#include "Animator.h"
#include "Texture.h"
#include "Object.h"
#include "TimeMgr.h"

Animation::Animation()
	:m_animator(nullptr), m_texture(nullptr), m_currentFrame(0), m_accumulatedTime(0.f), m_isFinished(false)
{

}

Animation::~Animation()
{

}

void Animation::update()
{
	if (m_isFinished) return;

	m_accumulatedTime += DeltaTime;

	if (m_accumulatedTime > m_frameInfos[m_currentFrame].speed)
	{
		m_currentFrame++;
		if (m_frameInfos.size() <= m_currentFrame)
		{
			m_currentFrame = -1;
			m_isFinished = true;
			m_accumulatedTime = 0.f;
			return;
		}
		m_accumulatedTime -= m_frameInfos[m_currentFrame].speed;
	}
}

void Animation::render(HDC _dc, Graphics* _graphic)
{
	if (m_isFinished) return;

	Object* obj = m_animator->getObj();
	Vector2 pos = obj->getPosition();

	Image* img = m_texture->GetImg();
	_graphic->DrawImage(img,
		(int)pos.x,
		(int)pos.y,
		(int)m_frameInfos[m_currentFrame].leftTop.x ,
		(int)m_frameInfos[m_currentFrame].leftTop.y ,
		(int)m_frameInfos[m_currentFrame].size.x,
		(int)m_frameInfos[m_currentFrame].size.y,
		UnitPixel);
}

void Animation::createAnimation(Texture* _texture, Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount)
{
	m_texture = _texture;

	AnimeFrameInfo frm = {};
	for (UINT i = 0; i < _cellCount; i++)
	{
		frm.speed = _speed;
		frm.size = _cellSize;
		frm.leftTop = _imgStartPos + _Step * i;
		m_frameInfos.push_back(frm);
	}
}


