#include "pch.h"
#include "BlueBG.h"

#include "Texture.h"
#include "ResourceMgr.h"

#include "Object.h"

BlueBG::BlueBG()
{
}

BlueBG::~BlueBG()
{
}

void BlueBG::initialize(Vector2 _position, const wstring& _key, const wstring& _relativePath)
{
	setPosition(_position);

	Texture* texture = getTexture();
	texture = ResourceMgr::GetInstance()->loadTexture(_key, _relativePath);
	setTexture(texture);
}

void BlueBG::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture;
	texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); //(*texture).getHeigt()?
	Vector2 pos = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)pos.x, (int)pos.y, width, height);
}
