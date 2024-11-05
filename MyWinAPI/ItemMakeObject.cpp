#include "ItemMakeObject.h"
#include "pch.h"

#include "Object.h"
#include "Texture.h"
#include "Item.h"
#include "MouseMgr.h"
#include "MouseCollider.h"
#include "Core.h"

ItemMakeObject::ItemMakeObject()
{
}

ItemMakeObject::ItemMakeObject(
	wstring _name, wstring _key, Vector2 _imagePosition, wstring _imagePath, string _cvImagePath, float _depth
	, wstring _createItemName, wstring _createItemKey, Vector2 _createIteminagmePosition, Vector2 _createIteminventoryPosition
	, wstring _createIteminGameImagePath, string _createIteminGamecvImagePath
	, wstring _createItemOutGameImagePath, string _createItemOutGamecvImagePath)
{
	setName(_name);
	setKey(_key);
	Vector2 pos = _imagePosition + MouseMgr::GetInstance()->getMouseOffset();
	
	// 새 아이템을 만들기 위한 속성들 초기화
	m_createItemName = _createItemName;
	m_createItemKey = _createItemKey;
	m_createIteminagmePosition = _createIteminagmePosition;

	m_createIteminGameImagePath = _createIteminGameImagePath;
	m_createIteminGamecvImagePath = _createIteminGamecvImagePath;
	m_createItemOutGameImagePath = _createItemOutGameImagePath;
	m_createItemOutGamecvImagePath = _createItemOutGamecvImagePath;

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
}

ItemMakeObject::~ItemMakeObject()
{
}

void ItemMakeObject::update()
{

}

void ItemMakeObject::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); //(*texture).getHeigt()?
	Vector2 position = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)position.x, (int)position.y, width, height);
}

void ItemMakeObject::onMouseClicked()
{
	Object* newItem = new Item(m_createItemName, m_createItemKey, m_createIteminagmePosition, m_createIteminventoryPosition
		, m_createIteminGameImagePath, m_createIteminGamecvImagePath, m_createItemOutGameImagePath, m_createItemOutGamecvImagePath, getDepth());
	//instantiate(newItem, GROUP_TYPE::UI_DRAGABLE);
}
