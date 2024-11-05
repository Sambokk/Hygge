#include "pch.h"
#include "CameraUpButton.h"

#include "Core.h"
#include "TimeMgr.h"
#include "ResourceMgr.h"
#include "MouseCollider.h"
#include "Texture.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CameraUpButton::CameraUpButton()
	:m_texture(nullptr), m_isOnWork(false), m_time(0)
{
	m_texture = ResourceMgr::GetInstance()->loadTexture(L"CameraUpButton", L"texture\\switch_button_up.png");

	createMouseCollider();
	int width = m_texture->getWidth();
	int hieght = m_texture->getHeight();
	getMouseCollider()->setSize(Vector2((float)width, (float)hieght));
}

CameraUpButton::~CameraUpButton()
{

}

void CameraUpButton::update()
{
	if (!m_isOnWork) return;

	m_time += DeltaTime;
	if (m_time > 0.005)
	{
		m_time -= 0.005f;
		int distance = 30;
		int offset = Core::GetInstance()->getCameraOffset();
		offset += distance;
		Core::GetInstance()->setCameraOffset(offset);

		///오브젝트들의 좌표 수정을 해준다.
		Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();


		const vector<Object*>& decoObjs = curScene->GetGroupObject(GROUP_TYPE::OBJ_REACT1);
		for (auto obj : decoObjs)
		{
			Vector2 pos = obj->getPosition();
			pos.y += distance;
			obj->setPosition(pos);
		}

		const vector<Object*>& bgObjs = curScene->GetGroupObject(GROUP_TYPE::OBJ_BG);
		for (auto obj : bgObjs)
		{
			Vector2 pos = obj->getPosition();
			pos.y += distance;
			obj->setPosition(pos);
		}

		const vector<Object*>& reactObjs = curScene->GetGroupObject(GROUP_TYPE::OBJ_REACT);
		for (auto obj : reactObjs)
		{
			Vector2 pos = obj->getPosition();
			pos.y += distance;
			obj->setPosition(pos);
		}


		///오프셋이 만족되면 작업을 중단한다.
		if (offset == 0)
		{
			m_isOnWork = false;
			m_time = 0;
			//destroy(this);
		}
	}
}

void CameraUpButton::render(HDC _dc, Graphics* _graphic)
{
	int width = m_texture->getWidth();
	int height = m_texture->getHeight();
	Vector2 pos = getPosition();

	Image* img = m_texture->GetImg();
	_graphic->DrawImage(img,
		(int)pos.x, (int)pos.y, width, height);
}

void CameraUpButton::onMouseClicked()
{
	SoundMgr::GetInstance()->stopBGM();
	SoundMgr::GetInstance()->setBlueUpSide(true);
	SoundMgr::GetInstance()->playBlueBGM();
	SoundMgr::GetInstance()->playSFX(0);
	m_isOnWork = true;
	//m_texture = ResourceMgr::GetInstance()->loadTexture(L"empty", L"texture\\empty.png");
}