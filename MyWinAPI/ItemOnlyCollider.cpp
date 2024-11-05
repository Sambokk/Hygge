#pragma once
#include "pch.h"
#include "ItemOnlyCollider.h"


#include "Texture.h"
#include "MouseCollider.h"
#include "Balloon.h"
#include "Fade_InOut.h"
#include "TimeMgr.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "BlueBG.h"
#include "Core.h"
#include "MouseMgr.h"
#include "Moon.h"
#include "SoundMgr.h"
#include "Item.h"
#include "MouseBubble.h"
#include "EventMgr.h"
#include "Fade_InOut.h"


Vector2 ItemOnlyCollider::m_cavePos = { 0.f,0.f };
bool ItemOnlyCollider::m_isGameEnd = false;
bool ItemOnlyCollider::m_isGameEndReal = false;
float ItemOnlyCollider::m_gameEndTime  = 0.f;

ItemOnlyCollider::ItemOnlyCollider(wstring _name, wstring _key, Vector2 _pos, wstring _path, string _cvpath, float _depth)
	:m_nightingTime(0.f), m_isNight(false), m_isNightingEnd(false), m_isWitchSpawn(false)
	, m_isMermaidAbleToClick(true), m_isShipAbleToClick(true), m_isWitchAbleToClick(true)
	, m_shipTime(0.f), m_witchTime(0.f), m_mermaidTime(0.f), m_bubbleTime(0.f)
	, m_witchsCollectionCount(0)
{
	setName(_name);
	setPosition(_pos);
	setDepth(_depth);

	createTexture(_key, _path);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	Mat myImg = imread(_cvpath, IMREAD_ANYCOLOR);
	cvtColor(myImg, myImg, COLOR_BGR2GRAY);
	threshold(myImg, myImg, 1, 255, THRESH_BINARY); //���� ���� 1 �̻��� �κ��� ��� 255�� �ٲپ��ش�.
	getMouseCollider()->createImgCollider(myImg);
	//imshow(_cvpath, myImg);
}

ItemOnlyCollider::~ItemOnlyCollider()
{

}


void ItemOnlyCollider::update()
{
	//��ǰ ������ ���� ������ ��ġ ������ ����
	if (this->getName() == L"Cave")
	{
		m_cavePos = this->getPosition();
	}

	
	//�ڿ������� ��->�� ��ȯ
	if (m_isNight)
	{
		m_nightingTime += DeltaTime;
		if (0.5f < m_nightingTime && !m_isNightingEnd)
		{
			Object* fi = new Fade_InOut(true);
			instantiate(fi, GROUP_TYPE::UI_SETTING_BG);

			createNightObject();

			m_isNightingEnd = true;
			m_nightingTime = 0;
		}
	}

	//��ǳ���� ������� ���� �ٽ� �����Ǵ� ���� ���´�
	if (!m_isWitchAbleToClick)
	{
		m_witchTime += DeltaTime;
		if (3.f < m_witchTime)
		{
			m_isWitchAbleToClick = true;
			m_witchTime = 0;
		}
	}

	if (!m_isShipAbleToClick)
	{
		m_shipTime += DeltaTime;
		if (3.f< m_shipTime)
		{
			m_isShipAbleToClick = true;
			m_shipTime = 0;
		}
	}

	if (!m_isMermaidAbleToClick)
	{
		m_mermaidTime += DeltaTime;
		if (3.f< m_mermaidTime)
		{
			m_isMermaidAbleToClick = true;
			m_mermaidTime = 0;
		}
	}


	//���࿡�� �� ������ 4���� �����Ǹ� ������ ������Ų��.
	if (m_witchsCollectionCount == 4)
	{
		SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_INTERACT);
		int a = EventMgr::GetInstance()->getEventOrderIndex();

		m_witchsCollectionCount = -1;

		Object* id_Magic_Potion_IG = new Item(L"id_Magic_Potion_IG", L"id_Magic_Potion_IG", adjustOffset(Vector2(494.f, 1079.f),0.38) , Vector2(28.f, 2267.f)
			, L"texture\\id_Magic_Potion_IG.png", "content/texture/id_Magic_Potion_IG.png"
			, L"texture\\id_Magic_Potion_OG.png", "content/texture/id_Magic_Potion_OG.png", 0.38);
		instantiate(id_Magic_Potion_IG, GROUP_TYPE::OBJ_REACT); // ���� ����
	}


	//Ư�� ������ �� �������� ��ǰ�� ���´�. (������� ���� ��, �������� ���� ��)
	if (  (EventMgr::GetInstance()->getEventOrderIndex() == 17)  
		|| (EventMgr::GetInstance()->getEventOrderIndex() == 21) )
	{
		void srand(unsigned int seed);
		int randomTime = (rand() % 60 + 20);
		
		m_bubbleTime += DeltaTime;
		if (((float)randomTime / 10) < m_bubbleTime)
		{
			m_bubbleTime = 0.f;

			int randomIntX = (rand() % 80);
			int randomIntY = (rand() % 40);

			Object* bubble = new(MouseBubble);
			bubble->setPosition(Vector2 ( m_cavePos.x + (float)randomIntX + 70
										, m_cavePos.y + (float)randomIntY + 80 ));
			instantiate(bubble, GROUP_TYPE::OBJ_REACT1);
		}
	}


	//���� ���� ȭ�� ���
	if (m_isGameEnd)
	{
		m_gameEndTime += DeltaTime;
		if (3.f * 5 < m_gameEndTime)
		{
			m_isGameEnd = false;
						
			//���̵� �ƿ� ȿ�� ȣ���ϱ�
			Object* f = new Fade_InOut(false, true); // ȭ�� ��ȯ
			instantiate(f, GROUP_TYPE::UI_SETTING_BG);

			m_isGameEndReal = true;
		}
	}

	if (m_isGameEndReal)
	{
		m_gameEndTime += DeltaTime;
		if ((3.5f * 5 - 0.5f) < m_gameEndTime)
		{
			//���� ���� �ʱ�ȭ
			m_isGameEnd = false;
			m_gameEndTime = 0.f;
			m_isGameEndReal = false;

			//�� �̵�
			changeScene(SCENE_TYPE::TITLE);
		}
	}
}

void ItemOnlyCollider::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); //(*texture).getHeigt()?
	Vector2 position = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)position.x, (int)position.y, width, height);
}

void ItemOnlyCollider::onMouseClicked()
{
	//���డ ��ǳ�� ����
	if (this->getName() == L"id_Witch_IG" && m_isWitchAbleToClick)
	{
		Object* b3 = new Balloon(L"witchBalloon", L"witchBalloon", adjustOffset(Vector2(542.f, 1018.f), 0.38f), L"texture\\Balloon_003.png", "content/texture/Balloon_003.png", 0.38f);
		instantiate(b3, GROUP_TYPE::OBJ_REACT);
		m_isWitchAbleToClick = false;

		SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
	}

	//�����ξ ��ǳ�� ���� ///���� �ʿ�!!
	if (this->getName() == L"id_Mermaid_Tail_IG" && m_isMermaidAbleToClick)
	{
		Object* b1 = new Balloon(L"mermaidBalloon", L"mermaidBalloon", adjustOffset(Vector2(760.f, 297.f), 0.38f), L"texture\\Balloon_001.png", "content/texture/Balloon_001.png", 0.10f);
		instantiate(b1, GROUP_TYPE::OBJ_REACT);
		m_isMermaidAbleToClick = false;

		SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
	}

	//�谡 ��ǳ�� ����
	if (this->getName() == L"id_Ship" && m_isShipAbleToClick)
	{
		Object* b2 = new Balloon(L"shipBalloon", L"shipBalloon", adjustOffset(Vector2(578.f, 378.f), 0.38f), L"texture\\Balloon_002.png", "content/texture/Balloon_002.png", 0.10f);
		instantiate(b2, GROUP_TYPE::OBJ_REACT);
		m_isShipAbleToClick = false;

		SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
	}

	
	
	//���� ���� Ŭ���ϸ� -> ���� �Ǳ�
	if (this->getName() == L"Cave" && !m_isNight && (EventMgr::GetInstance()->getEventOrderIndex() == 17))
	{
		EventMgr::GetInstance()->nextSceneEventOrder();
		setNight();
		SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_CHANGE_3);
	}
}

void ItemOnlyCollider::onMouseCollision(Object* _other)
{
	//������ �������� �޾��� �� -> ���� ����
	if (this->getName() == L"Cave" && _other->getName() == L"id_Moonshine_IGO")
	{
		EventMgr::GetInstance()->nextSceneEventOrder();
		m_isWitchSpawn = true;

		Object* id_Witch_IG = new ItemOnlyCollider(L"id_Witch_IG", L"id_Witch_IG", adjustOffset(Vector2(349.f, 1043.f), 0.38f),
			L"texture\\id_Witch_IG.png", "content/texture/id_Witch_IG.png", 0.38f);
		instantiate(id_Witch_IG, GROUP_TYPE::OBJ_REACT1);

		SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_CHANGE_1);

		_other->setObtained(true);
	}

	/*
	//���డ ���� 2��, ��ȣ 1��, ���� 1�� �޾��� ��
	if ((this->getName() == L"id_Witch_IG" && _other->getName() == L"id_Clam_Common001_IGO")
		|| (this->getName() == L"id_Witch_IG" && _other->getName() == L"id_Clam_Common002_IGO")
		|| (this->getName() == L"id_Witch_IG" && _other->getName() == L"id_Coral_Leef_IGO")
		|| (this->getName() == L"id_Witch_IG" && _other->getName() == L"id_Pearl_IGO")
		)
	{
		
		m_witchsCollectionCount++;
	}
	*/


	//���డ �������� ����
	if (this->getName() == L"id_Witch_IG")
	{
		if (_other->getName() == L"id_Clam_Common001_IGO" && !_other->getObtained())
		{
			m_witchsCollectionCount++;
			_other->setObtained(true);
			SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_CHANGE_1);
		}

		if (_other->getName() == L"id_Clam_Common002_IGO" && !_other->getObtained())
		{
			m_witchsCollectionCount++;
			_other->setObtained(true);
			SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_CHANGE_2);
		}

		if (_other->getName() == L"id_Coral_Leef_IGO" && !_other->getObtained())
		{
			m_witchsCollectionCount++;
			_other->setObtained(true);
			SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_CHANGE_3);
		}

		if (_other->getName() == L"id_Pearl_IGO" && !_other->getObtained())
		{
			m_witchsCollectionCount++;
			_other->setObtained(true);
			SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_CHANGE_1);
		}
	}




	//�ξ ������ �޾��� �� -> ����
	if (this->getName() == L"id_Mermaid_Tail_IG" && _other->getName() == L"id_Magic_Potion_IGO")
	{	
		//�ΰ��ӿ� �ٸ��޸� �ξ� ����
		Object* id_Mermaid_Legs_IG = new ItemOnlyCollider(L"id_Mermaid_Legs_IG", L"id_Mermaid_Legs_IG", adjustOffset(Vector2(890.f, 250.f), 0.1f)
			, L"texture\\id_Mermaid_Legs_IG.png", "content/texture/id_Mermaid_Legs_IG.png", 0.1f);
		instantiate(id_Mermaid_Legs_IG, GROUP_TYPE::OBJ_REACT); 

		//�ص� �̺�Ʈ ����
		startEndingEvent();
		EventMgr::GetInstance()->SetBlueBookClear();

		//���� �ִ� �ξ�� ����
		destroy(this);
	}
}




void ItemOnlyCollider::setNight()
{
	SoundMgr::GetInstance()->setBlueNight(true);
	SoundMgr::GetInstance()->stopBGM();
	SoundMgr::GetInstance()->playBlueBGM();

	m_isNight = true;

	//���̵� �ƿ�
	Object* fo = new Fade_InOut(false);
	instantiate(fo, GROUP_TYPE::UI_SETTING_BG);
}



void ItemOnlyCollider::createNightObject()
{
	//OBJ_BG�±� ��� ����
	Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
	const vector<Object*>& bg = curScene->GetGroupObject(GROUP_TYPE::OBJ_BG);
	for (auto obj : bg)
	{
		destroy(obj);
	}

	//OBJ_BG�� �� ���, �� �ٴ� �ֱ�
	Object* BO_sky_night = new BlueBG; // �� ���
	BO_sky_night->initialize(Vector2(0.f, (float)Core::GetInstance()->getCameraOffset()), L"BO_sky_night", L"texture\\BO_sky_night.bmp");
	instantiate(BO_sky_night, GROUP_TYPE::OBJ_BG);

	Object* BO_ocean_night002 = new BlueBG; // �� �ٴ� 002
	BO_ocean_night002->initialize(adjustOffset(Vector2(0.f, 430.f), 0.03f), L"BO_ocean_night002", L"texture\\Background_Ocean_Night_002.png");
	BO_ocean_night002->setDepth(0.03f);
	instantiate(BO_ocean_night002, GROUP_TYPE::OBJ_BG);

	Object* BO_ocean_night003 = new BlueBG; // �� �ٴ� 003
	BO_ocean_night003->initialize(adjustOffset(Vector2(0.f, 490.f), 0.15f), L"BO_ocean_night003", L"texture\\Background_Ocean_Night_003.png");
	BO_ocean_night003->setDepth(0.15f);
	instantiate(BO_ocean_night003, GROUP_TYPE::OBJ_BG);

	Object* BO_ocean_night001 = new BlueBG; // �� �ٴ� 001
	BO_ocean_night001->initialize(adjustOffset(Vector2(0.f, 520.f), 0.4f), L"BO_ocean_night001", L"texture\\Background_Ocean_Night_001.png");
	BO_ocean_night001->setDepth(0.4f);
	instantiate(BO_ocean_night001, GROUP_TYPE::OBJ_BG);

	//���� ����
	Object* id_Moon = new Moon(L"id_Moon", L"id_Moon", adjustOffset(Vector2(815.f, 23.f),0.f)  
		, L"texture\\id_Moon.png", "content/texture/id_Moon.png"
		, L"id_Moonshine_IG", L"id_Moonshine_IG", Vector2(890.f, 98.f), Vector2(28.f, 2140.f)
		, L"texture\\id_Moonshine_IG.png", "content/texture/id_Moonshine_IG.png"
		, L"texture\\id_Moonshine_OG.png", "content/texture/id_Moonshine_OG.png"
		, 0.f, 0, false);
	instantiate(id_Moon, GROUP_TYPE::OBJ_REACT);
}


Vector2 ItemOnlyCollider::adjustOffset(Vector2 _orginPos, float _depth)
{
	Vector2 p = _orginPos;
	p = p + MouseMgr::GetInstance()->getMouseOffset() * _depth;
	p.y += (float)Core::GetInstance()->getCameraOffset();

	return p;
}



void ItemOnlyCollider::startEndingEvent()
{
	SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::STAGE_CLEAR);
	m_isGameEnd = true;
	//UI �� �����
	{
		Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
		const vector<Object*>& ui = curScene->GetGroupObject(GROUP_TYPE::UI);
		for (auto obj : ui)
		{
			destroy(obj);
		}

		const vector<Object*>& uid = curScene->GetGroupObject(GROUP_TYPE::UI_DRAGABLE);
		for (auto obj : uid)
		{
			destroy(obj);
		}

		const vector<Object*>& uiu = curScene->GetGroupObject(GROUP_TYPE::UI_UNFOUND);
		for (auto obj : uiu)
		{
			destroy(obj);
		}

		const vector<Object*>& uis = curScene->GetGroupObject(GROUP_TYPE::UI_USED);
		for (auto obj : uis)
		{
			destroy(obj);
		}

		const vector<Object*>& inv = curScene->GetGroupObject(GROUP_TYPE::INVENTORY_BG);
		for (auto obj : inv)
		{
			destroy(obj);
		}

		const vector<Object*>& a = curScene->GetGroupObject(GROUP_TYPE::UI_SETTING);
		for (auto obj : a)
		{
			destroy(obj);
		}

		const vector<Object*>& b = curScene->GetGroupObject(GROUP_TYPE::UI_SETTING_BG);
		for (auto obj : b)
		{
			destroy(obj);
		}
	
		const vector<Object*>& c = curScene->GetGroupObject(GROUP_TYPE::UI_BG);
		for (auto obj : c)
		{
			destroy(obj);
		}
	}
}
