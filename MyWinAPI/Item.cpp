#include "pch.h"
#include "Item.h"

#include "Texture.h"
#include "ResourceMgr.h"
#include "MouseMgr.h"
#include "MouseCollider.h"
#include "Core.h"
#include "BlueBG.h"
#include "Scene.h"
#include "SoundMgr.h"

#include <codecvt>
#include <algorithm>
#include <regex>
Item::Item()
{

}

//인게임 오브젝트
Item::Item(wstring _name, wstring _key, Vector2 _imagePosition, Vector2 _inventoryPosition, wstring _imagePath, string _cvImagePath, float _depth)
	:m_inventoryPosition(_inventoryPosition)

{
	setName(_name);
	setKey(_key);
	Vector2 pos = _imagePosition + MouseMgr::GetInstance()->getMouseOffset();
	pos.y += Core::GetInstance()->getCameraOffset();
	setPosition(_imagePosition);
	setImagePath(_imagePath);
	setCvPath(_cvImagePath);
	setDepth(_depth);

	createTexture(_key, _imagePath);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	Mat myImg = imread(_cvImagePath, IMREAD_ANYCOLOR);
	cvtColor(myImg, myImg, COLOR_BGR2GRAY);
	threshold(myImg, myImg, 1, 255, THRESH_BINARY); //색상 값이 1 이상인 부분은 모두 255로 바꾸어준다.
	getMouseCollider()->createImgCollider(myImg);
	//imshow("d", myImg);
}

Item::Item(wstring _name, wstring _key, Vector2 _imagePosition, Vector2 _inventoryPosition,
	wstring _inGameImagePath, string _inGamecvImagePath
	, wstring _outGameImagePath, string _outGamecvImagePath
	, float _depth)
{
	setName(_name);
	setKey(_key);
	Vector2 pos = _imagePosition + MouseMgr::GetInstance()->getMouseOffset();
	pos.y += Core::GetInstance()->getCameraOffset();
	setPosition(_imagePosition);
	setImagePath(_inGameImagePath);
	setCvPath(_inGamecvImagePath);
	setDepth(_depth);

	m_inventoryPosition = _inventoryPosition;
	m_outGameImagePath = _outGameImagePath;
	m_outGamecvImagePath = _outGamecvImagePath;

	createTexture(_key, _inGameImagePath);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	Mat myImg = imread(_inGamecvImagePath, IMREAD_ANYCOLOR);
	cvtColor(myImg, myImg, COLOR_BGR2GRAY);
	threshold(myImg, myImg, 1, 255, THRESH_BINARY); //색상 값이 1 이상인 부분은 모두 255로 바꾸어준다.
	getMouseCollider()->createImgCollider(myImg);
	//imshow(_inGamecvImagePath, myImg);
}


Item::Item(wstring _name, wstring _key, Vector2 _imagePosition, Vector2 _inventoryPosition
	, wstring _inGameImagePath, string _inGamecvImagePath
	, wstring _outGameImagePath, string _outGamecvImagePath
	, float _depth, int _sfxs)
{
	setName(_name);
	setKey(_key);
	Vector2 pos = _imagePosition + MouseMgr::GetInstance()->getMouseOffset();
	pos.y += Core::GetInstance()->getCameraOffset();
	setPosition(_imagePosition);
	setImagePath(_inGameImagePath);
	setCvPath(_inGamecvImagePath);
	setDepth(_depth);

	m_inventoryPosition = _inventoryPosition;
	m_outGameImagePath = _outGameImagePath;
	m_outGamecvImagePath = _outGamecvImagePath;

	createTexture(_key, _inGameImagePath);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	Mat myImg = imread(_inGamecvImagePath, IMREAD_ANYCOLOR);
	cvtColor(myImg, myImg, COLOR_BGR2GRAY);
	threshold(myImg, myImg, 1, 255, THRESH_BINARY); //색상 값이 1 이상인 부분은 모두 255로 바꾸어준다.
	getMouseCollider()->createImgCollider(myImg);
	//imshow("d", myImg);

	m_sfxs = (UINT)_sfxs;

}


//인벤토리에 들어갈 아이템
Item::Item(wstring _name, wstring _key, Vector2 _inventoryPosition, wstring _imagePath)
{
	setName(_name);
	setKey(_key);
	setPosition(
		Vector2(_inventoryPosition.x
			, _inventoryPosition.y + MouseMgr::GetInstance()->getInventoryOffset())
	); // 인벤토리에 위치할 

	m_inventoryPosition = _inventoryPosition;

	createTexture(_key, _imagePath);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	//wstring -> string
	string cvPath = pathToCvPAth(_imagePath);

	Mat myImg = imread(cvPath, IMREAD_ANYCOLOR);
	cvtColor(myImg, myImg, COLOR_BGR2GRAY);
	threshold(myImg, myImg, 1, 255, THRESH_BINARY);
	getMouseCollider()->createImgCollider(myImg);
	//imshow(cvPath, myImg);
}



Item::Item(wstring _name, wstring _key, Vector2 _inventoryPosition, wstring _imagePath, string _cvImagePath)
{
	setName(_name);
	setKey(_key);
	setPosition(
		Vector2(
			_inventoryPosition.x
			, _inventoryPosition.y + MouseMgr::GetInstance()->getInventoryOffset())
	); // 인벤토리에 위치할 

	m_inventoryPosition = _inventoryPosition;

	createTexture(_key, _imagePath);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	Mat myImg = imread(_cvImagePath, IMREAD_ANYCOLOR);
	cvtColor(myImg, myImg, COLOR_BGR2GRAY);
	threshold(myImg, myImg, 1, 255, THRESH_BINARY); //색상 값이 1 이상인 부분은 모두 255로 바꾸어준다.
	getMouseCollider()->createImgCollider(myImg);
	//imshow("d", myImg);
}

Item::~Item()
{
	//if (L"id_Coral_Singleton001_IGO" == getName() || getName() == L"id_Coral_Singleton002_IGO")
	//{
	//	Object* inventoryItemChecked = new Item(getName() + L"C", getKey() + L"C"
	//		, Vector2(m_inventoryPosition.x - 720.f, m_inventoryPosition.y - 720.f), L"texture\\Setting_check.png");
	//	instantiate(inventoryItemChecked, GROUP_TYPE::UI_DRAGABLE);
	//}
}

void Item::update()
{
	/////// 마녀 퀘스트 
	if (getObtained())
	{
		Object* inventoryItemChecked = new Item(getName() + L"C", getKey() + L"C"
			, Vector2(50.f, m_inventoryPosition.y + 20.f), L"texture\\Check.png");
		instantiate(inventoryItemChecked, GROUP_TYPE::UI_USED);
		setObtained(false);
		destroy(this);
	}
	
	// 산호 군락체 없어지기
	if (getName() == L"id_Coral_Leef_IG_BG" &&
		EventMgr::GetInstance()->getBlueEventOrder() == L"id_Fish_Bluetang_IG")
	{
		if (!getObtained())
		{
			setObtained(true);
			destroy(this);
		}

	}

	// 달조각 없어지기
	if (L"id_Moonshine_IG" == getName() &&
		EventMgr::GetInstance()->getBlueEventOrder() == L"id_Witch_IG")
	{
		if (getObtained())
		{	// 땡떙 표시
			Object* Check = new Item(getName() + L"C", getKey() + L"C"
				, Vector2(40.f, m_inventoryPosition.y + 30.f), L"texture\\Check.png");
			instantiate(Check, GROUP_TYPE::UI_USED);

			setObtained(false);
			destroy(this);
		}
	}
	
}

void Item::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); //(*texture).getHeigt()?
	Vector2 position = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)position.x, (int)position.y, width, height);
}

void Item::onMouseClicked()
{
	// 현재 순서일 때만 실행
	if (EventMgr::GetInstance()->getBlueEventOrder() == getName())
	{
		Object* inventoryItem = new Item(getName() + L"O", getKey() + L"O", m_inventoryPosition, m_outGameImagePath);
		instantiate(inventoryItem, GROUP_TYPE::UI_DRAGABLE);
		destroy(this);

		EventMgr::GetInstance()->nextSceneEventOrder();

		SoundMgr::GetInstance()->playSFX(m_sfxs);
	}
	else
	{
		//미클릭 소리
		SoundMgr::GetInstance()->playSFX(12);

	}
}

void Item::onMouseCollision(Object* _otherItem)
{
	// 달조각 -> 동굴 = 밤,마녀
	if (L"id_Moonshine_IG" == getName()) // 현재 이 아이템 이름이 달조각일때
	{
		if (_otherItem->getKey() == L"Cave" || _otherItem->getName() == L"Cave")
		{
			// 마녀 등장
			Object* id_Witch_IG = new BlueBG;
			id_Witch_IG->initialize(Vector2(349.f, 1043.f), L"id_Witch_IG", L"texture\\id_Witch_IG.png");
			id_Witch_IG->setDepth(0.38f);
			instantiate(id_Witch_IG, GROUP_TYPE::OBJ_REACT1); // 마녀

			//마법 포션
			Object* id_Magic_Potion_IG = new Item(L"id_Magic_Potion_IG", L"id_Magic_Potion_IG", Vector2(494.f, 1079.f), Vector2(28.f, 2267.f),
				L"texture\\id_Magic_Potion_IG.png", "content/texture/id_Magic_Potion_IG.png"
				, L"texture\\id_Magic_Potion_OG.png", "content/texture/id_Magic_Potion_OG.png", 0.38f);
			instantiate(id_Magic_Potion_IG, GROUP_TYPE::OBJ_REACT);

			destroy(this);
		}
	}


	// 산호1 + 산호2  
	if (L"id_Coral_Singleton001_IGO" == getName() && _otherItem->getName() == L"id_Coral_Singleton002_IGO")
	{

		// 땡떙 표시
		Object* inventoryItemChecked = new Item(getName() + L"C", getKey() + L"C"
			, Vector2(50.f, m_inventoryPosition.y + 60.f), L"texture\\Check.png");
		instantiate(inventoryItemChecked, GROUP_TYPE::UI_USED);

		//산호군락 등장
		Object* id_Coral_Leef_IG = new Item(L"id_Coral_Leef_IG", L"id_Coral_Leef_IG"
			, Vector2(

				813.f + MouseMgr::GetInstance()->getMouseOffset().x * 0.65f,
				1172.f + MouseMgr::GetInstance()->getMouseOffset().y * 0.65f + Core::GetInstance()->getCameraOffset()) //- 720.f)

			, Vector2(9.f, 1773.f)
			, L"texture\\id_Coral_Leef_IG.png", "content/texture/id_Coral_Leef_IG.png"
			, L"texture\\id_Coral_Leef_OG.png", "content/texture/id_Coral_Leef_OG.png", 0.65f);
		instantiate(id_Coral_Leef_IG, GROUP_TYPE::OBJ_REACT); // 산호군락

		destroy(this);
	}

	// 산호2 + 산호1 
	if (L"id_Coral_Singleton002_IGO" == getName())
	{
		if (_otherItem->getName() == L"id_Coral_Singleton001_IGO")
		{	// 땡떙 표시
			Object* Check = new Item(getName() + L"C", getKey() + L"C"
				, Vector2(40.f, m_inventoryPosition.y + 60.f), L"texture\\Check.png");
			instantiate(Check, GROUP_TYPE::UI_USED);

			destroy(this);
		}
	}


	
}


string Item::pathToCvPAth(wstring _path)
{
	wstring news = _path;
	static std::locale loc("");
	auto& facet = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);

	string s = "content/";
	s += std::wstring_convert<std::remove_reference<decltype(facet)>::type, wchar_t>(&facet).to_bytes(news);

	regex_replace(s, std::regex("\\\\"), "/");  // 수정된 부분

	return s;
}