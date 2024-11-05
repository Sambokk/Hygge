#include "pch.h"
#include "Book.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "Object.h"
#include "MouseCollider.h"
#include "TimeMgr.h"
#include "Fade_InOut.h"
#include "TimeMgr.h"
#include "SoundMgr.h"

Book::Book()
	:m_time(0), m_isReadyToChangeSceneBlue(false)
{
}

Book::~Book()
{
}

Book::Book(wstring _name, Vector2 _position, wstring _key, wstring _path)
	:m_time(0), m_isReadyToChangeSceneBlue(false)
{
	setName(_name);
	setPosition(_position);

	createTexture(_key, _path);
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();

	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));
}


void Book::initialize(Vector2 _position, const wstring& _key, const wstring& _relativePath)
{
	setPosition(_position);

	Texture* texture = getTexture();
	texture = ResourceMgr::GetInstance()->loadTexture(_key, _relativePath);
	setTexture(texture);
}


void Book::update()
{
	if (m_isReadyToChangeSceneBlue)
	{
		m_time += DeltaTime;
		if (m_time > 0.5f) changeScene(SCENE_TYPE::BLUE);
	}
}



void Book::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture;
	texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); 
	Vector2 pos = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)pos.x, (int)pos.y, width, height);
}


void Book::onMouseClicked()
{
	SoundMgr::GetInstance()->playSFX(12);

	if (this->getName() == L"blueBook" || this->getName() == L"BlueBook")
	{
		Object* f = new Fade_InOut(false);
		instantiate(f, GROUP_TYPE::UI_BG);

		m_isReadyToChangeSceneBlue = true;
	}
}

