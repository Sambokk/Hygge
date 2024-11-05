#include "pch.h"
#include "Object.h"
#include "ResourceMgr.h"

#include "MouseCollider.h"
#include "Animator.h"
#include "Texture.h"

Object::Object()
	: m_isActive(true)
	, m_depth(0)
	, m_key()
	, m_name()
	, m_cvPath()
	, m_imagePath()
	, m_scale{}
	, m_position{}
	, m_texture(nullptr)
	, m_mouseCollider(nullptr)
	, m_animator(nullptr)
{
}

Object::~Object()
{
	if (m_mouseCollider != nullptr)	{delete m_mouseCollider;}
	if (m_animator != nullptr) { delete m_animator; }
}


void Object::createTexture(wstring _key, wstring _path)
{
	m_texture = ResourceMgr::GetInstance()->loadTexture(_key, _path);
}

void Object::initialize(Vector2 _position, const wstring& _key, const wstring& _relativePath)
{
	setPosition(_position);
	m_texture = ResourceMgr::GetInstance()->loadTexture(_key, _relativePath);
}

void Object::createMouseCollider()
{
	m_mouseCollider = new MouseCollider;
	m_mouseCollider->m_owner = this;
}

void Object::createAnimator()
{
	m_animator = new Animator;
	m_animator->m_owner = this;
}

void Object::render(HDC _dc, Graphics* _grapics)
{
	componentRender(_dc, _grapics);
}

void Object::componentRender(HDC _dc, Graphics* _grapic)
{
	if (m_animator != nullptr)
	{
		m_animator->render(_dc, _grapic);
	}
}

void Object::update()
{
	if (m_isActive =! true)
	{
		destroy(this);
	}
}

void Object::finalUpdate()
{
	if (m_mouseCollider)
		m_mouseCollider->finalUpdate();
}