#include "pch.h"
#include "Moon.h"

#include "MouseMgr.h"
#include "Core.h"
#include "Texture.h"
#include "MouseCollider.h"
#include "Item.h"
#include "SoundMgr.h"

Moon::Moon()
	: m_newItemName()
	, m_newItemKey()
	, m_newItemImagePosition()
	, m_newItemInventoryPosition()
	, m_newIteinGamePath()
	, m_newIteinGamecvImagePath()
	, m_newIteoutGamePath()
	, m_newIteoutGamecvePath()
	, m_clickNum()
	, m_isGone()
{
}

Moon::Moon(wstring _name, wstring _key, Vector2 _imagePosition, wstring _imagePath, string _cvImagePath, wstring _newItemName, wstring _newItemKeym, Vector2 _newItemImagePosition, Vector2 _newItemInventoryPosition, wstring _newIteinGamePath, string _newIteinGamecvImagePath, wstring _newIteoutGamePath, string _newIteoutGamecvePath
	, float _depth, int _clickNum, bool _isGone)
	: m_newItemName(_newItemName)
	, m_newItemKey(_newItemKeym)
	, m_newItemImagePosition(_newItemImagePosition)
	, m_newItemInventoryPosition(_newItemInventoryPosition)
	, m_newIteinGamePath(_newIteinGamePath)
	, m_newIteinGamecvImagePath(_newIteinGamecvImagePath)
	, m_newIteoutGamePath(_newIteoutGamePath)
	, m_newIteoutGamecvePath(_newIteoutGamecvePath)
	, m_clickNum(_clickNum)
	, m_isGone(_isGone)

{
	setName(_name);
	setKey(_key);
	Vector2 pos = _imagePosition + MouseMgr::GetInstance()->getMouseOffset();
	pos.y += Core::GetInstance()->getCameraOffset()*_depth;
	setPosition(pos);
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
}

Moon::~Moon()
{
}

void Moon::update()
{
}

void Moon::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); //(*texture).getHeigt()?
	Vector2 position = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)position.x, (int)position.y, width, height);
}

void Moon::onMouseClicked()
{	/// 순서일 떄만 실행
	if (EventMgr::GetInstance()->getBlueEventOrder() == getName()) // 해당 아이템 차례일 때
	{
		if (!m_clickNum)
		{
			
			Object* newItme = new Item(m_newItemName, m_newItemKey, m_newItemImagePosition, m_newItemInventoryPosition
				, m_newIteinGamePath, m_newIteinGamecvImagePath // 인게임 경로
				, m_newIteoutGamePath, m_newIteoutGamecvePath
				, getDepth());
			//instantiate(newItme, GROUP_TYPE::OBJ_REACT);
			
			
			if (getName() == L"id_Pearl_Oyster_Closed_IG")
			{
				SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_CHANGE_1);
				instantiate(newItme, GROUP_TYPE::OBJ_REACT1);

				// 진주
				Object* id_Pearl_IG = new Item(L"id_Pearl_IG", L"id_Pearl_IG", Vector2(554.f, 520.f), Vector2(28.f, 1640.f)
					, L"texture\\id_Pearl_IG.png", "content/texture/id_Pearl_IG.png"
					, L"texture\\id_Pearl_OG.png", "content/texture/id_Pearl_OG.png"
					, getDepth());

				instantiate(id_Pearl_IG, GROUP_TYPE::OBJ_REACT);
			}
			else
			{
				instantiate(newItme, GROUP_TYPE::OBJ_REACT);
			}
			if (m_isGone)
			{
				destroy(this);
			}
			EventMgr::GetInstance()->nextSceneEventOrder();
		}
		m_clickNum -= 1;
		if(this->getName() == L"id_Pearl_Oyster_Closed_IG") SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
		else SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_PICK);
	}
}

Vector2 Moon::adjustOffset(Vector2 _orginPos, float _depth)
{
	Vector2 p = _orginPos;
	p = p + MouseMgr::GetInstance()->getMouseOffset() * _depth;
	p.y += (float)Core::GetInstance()->getCameraOffset();

	return p;
}
