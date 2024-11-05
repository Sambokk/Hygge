#include "pch.h"
#include "MouseBubble.h"

#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"

MouseBubble::MouseBubble()
	:m_texture(nullptr), m_time(0), m_lifeTime(0)
{
	m_texture = ResourceMgr::GetInstance()->loadTexture(L"mouseBubble", L"texture\\mousepoint(50x50).png");
	createAnimator();
	getAnimator()->createAnimation(L"mouseBubble", m_texture,
		Vector2(0.f, 0.f), Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.1f, 5);
	getAnimator()->play(L"mouseBubble", false);
}

MouseBubble::~MouseBubble()
{

}

void MouseBubble::update()
{
	getAnimator()->update();

	m_time += DeltaTime;
	if (m_time > 0.015)
	{
		m_time -= 0.015;
		
		Vector2 pos = getPosition();
		pos.y -= 2;
		setPosition(pos);
		m_lifeTime++;
	}
}