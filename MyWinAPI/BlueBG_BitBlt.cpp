#include "pch.h"
#include "BlueBG_BitBlt.h"

#include "Texture.h"
#include "ResourceMgr.h"

BlueBG_BitBlt::BlueBG_BitBlt()
{
}

BlueBG_BitBlt::~BlueBG_BitBlt()
{
}


void BlueBG_BitBlt::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight();
	Vector2 pos = getPosition();

	BitBlt(_dc
	, (int)(pos.x) , (int)(pos.y)
	, width, height
	, _dc, 0, 0, SRCCOPY);
}


