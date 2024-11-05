#include "pch.h"

#include "Animator.h"
#include "function.h"
#include "Animation.h"


Animator::Animator()
	:m_owner(nullptr), m_currentAnimation(nullptr), isRepeat(false)
{

}


Animator::~Animator()
{
	safeDeleteMap(m_animations);
}


void Animator::createAnimation(const wstring& _name, Texture* _texture,
	Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount)
{

	Animation* ani = findAnimation(_name);
	assert(ani == nullptr);

	Animation* anime = new Animation;
	anime->setName(_name);
	anime->m_animator = this;
	anime->createAnimation(_texture, _imgStartPos, _cellSize, _Step, _speed, _cellCount);

	m_animations.insert(make_pair(_name, anime));

}

Animation* Animator::findAnimation(const wstring& _name)
{
	map<wstring, Animation*>::iterator iter = m_animations.find(_name);

	if (iter == m_animations.end())
		return nullptr;

	return iter->second;
}


void Animator::play(const wstring& _name, bool _repeat)
{
	m_currentAnimation = findAnimation(_name);
	isRepeat = _repeat;
}


void Animator::update()
{
	if (m_currentAnimation != nullptr)
	{
		m_currentAnimation->update();
		if (isRepeat && m_currentAnimation->isAnimationFinished())
		{
			m_currentAnimation->setFrame(0);
		}
	}
}


void Animator::render(HDC _dc, Graphics* _graphic)
{
	if (m_currentAnimation != nullptr)
		m_currentAnimation->render(_dc, _graphic);
}

