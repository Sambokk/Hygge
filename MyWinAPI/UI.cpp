#include "pch.h"
#include "UI.h"

#include "Texture.h"
#include "ResourceMgr.h"
#include "MouseCollider.h"
#include "Core.h"
#include "SoundMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "TimeMgr.h"

bool UI::m_soundPlay = true;

UI::UI(wstring _name, Vector2 _position, wstring _key, wstring _path, int _scene)
	:m_time(0)
{
	m_sceneType = _scene;
	setName(_name);
	setPosition(_position);

	createTexture(_key, _path);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));
}

UI::UI(wstring _name, Vector2 _position, wstring _key, wstring _path, string _cvpath, int _scene)
{
	m_sceneType = _scene;
	setName(_name);
	setPosition(_position);

	createTexture(_key, _path);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	Mat myImg = imread(_cvpath, IMREAD_ANYCOLOR);
	cvtColor(myImg, myImg, COLOR_BGR2GRAY);
	threshold(myImg, myImg, 1, 255, THRESH_BINARY); //색상 값이 1 이상인 부분은 모두 255로 바꾸어준다.
	getMouseCollider()->createImgCollider(myImg);
	//imshow(_cvpath, myImg);
}

UI::~UI()
{
}

void UI::update()
{

}

void UI::render(HDC _dc, Graphics* _graphic)
{
	if (this->getName() == L"soundButtonOn" && !m_soundPlay) return;

	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); //(*texture).getHeigt()?
	Vector2 position = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)position.x, (int)position.y, width, height);

	if (this->getName() == L"settingBG")
		int a = 0;
}

void UI::onMouseClicked()
{
	SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
	if (this->getName() == L"settingButton")
	{
		Object* settingBG = new UI(L"settingBG", Vector2(0.f, 0.f), L"settingBG", L"texture\\setting_bg.png",this->m_sceneType);
		instantiate(settingBG, GROUP_TYPE::UI_SETTING_BG);
		
		Object* soundButtonOn = new UI(L"soundButtonOn", Vector2(580.f, 270.f), L"soundButtonOn", L"texture\\sound_On.png", this->m_sceneType);
		instantiate(soundButtonOn, GROUP_TYPE::UI_SETTING);

		Object* soundButtonOff = new UI(L"soundButtonOff", Vector2(580.f, 270.f), L"soundButtonOff", L"texture\\sound_Off.png", this->m_sceneType);
		instantiate(soundButtonOff, GROUP_TYPE::UI_SETTING);

		Object* backButton = new UI(L"backButton", Vector2(530.f, 380.f), L"backButton", L"texture\\backButton.png", this->m_sceneType);
		instantiate(backButton, GROUP_TYPE::UI_SETTING);

		if (SceneMgr::GetInstance()->getCurrentScene()->GetName() != L"Title Scene")
			{
			Object* homeButton = new UI(L"homeButton", Vector2(630.f, 380.f), L"homeButton", L"texture\\homeButton.png", this->m_sceneType);
			instantiate(homeButton, GROUP_TYPE::UI_SETTING);
			}
		else 
		{
			Object* homeButton = new UI(L"homeButton", Vector2(630.f, 380.f), L"homeButton", L"texture\\homeButton.png", this->m_sceneType);
			instantiate(homeButton, GROUP_TYPE::UI_SETTING_BG);
		}

		Object* exitButton = new UI(L"exitButton", Vector2(730.f, 380.f), L"exitButton", L"texture\\exitButton.png", this->m_sceneType);
		instantiate(exitButton, GROUP_TYPE::UI_SETTING);
	}

	if (this->getName() == L"soundButtonOff")
	{
		if (m_soundPlay)
		{
			m_soundPlay = false;
			SoundMgr::GetInstance()->adjustBGMVolume(0.f);
			SoundMgr::GetInstance()->adjustSFXVolume(0.f);
		}
		else
		{
			m_soundPlay = true;
			SoundMgr::GetInstance()->setVolumeZero(false);
			SoundMgr::GetInstance()->adjustBGMVolume(1.f);
			SoundMgr::GetInstance()->adjustSFXVolume(1.f);
			
			if (this->m_sceneType == (int)SCENE_TYPE::BLUE)
			{
				SoundMgr::GetInstance()->playBlueBGM();
			}
		}
	}


	if (this->getName() == L"homeButton")
	{
		changeScene(SCENE_TYPE::TITLE);
	}

	if (this->getName() == L"exitButton")
	{
		SendMessage(Core::GetInstance()->getMainHwnd(), WM_CLOSE, 0, 0);
	}

	if (this->getName() == L"backButton")
	{
		destroyThisWindow();
	}
}


void UI::destroyThisWindow()
{
	Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
	const vector<Object*>& bg = curScene->GetGroupObject(GROUP_TYPE::UI_SETTING_BG);
	for (auto obj : bg)
	{
		destroy(obj);
	}

	const vector<Object*>& bt = curScene->GetGroupObject(GROUP_TYPE::UI_SETTING);
	for (auto obj : bt)
	{
		destroy(obj);
	}
}
