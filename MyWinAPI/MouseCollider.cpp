#include "pch.h"
#include "MouseCollider.h"

#include "Object.h"
#include "Core.h"

#include "cv.h"

UINT MouseCollider::m_idIndex = 0;

MouseCollider::MouseCollider()
	:m_owner(nullptr)
	, m_id(m_idIndex++)
{
	m_imgCollider = cv::Mat();
}

MouseCollider::~MouseCollider()
{

}



void MouseCollider::finalUpdate()
{
	Vector2 colliderPos = m_owner->getPosition();
	m_fianlPos = colliderPos;
}
