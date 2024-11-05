#include "pch.h"
#include "StartBG.h"
#include "Texture.h"

StartBG::StartBG()
{
}

StartBG::~StartBG()
{

}

void StartBG::update()
{
}

void StartBG::render(HDC _dc)
{

	if (getTexture() != nullptr)
	{
	int width = getTexture()->getWidth(); //(*texture).getWidth()
	int height = getTexture()->getHeight();
	Vector2 position = getPosition();

	{
		Graphics G(_dc);
		Image* img = getTexture()->GetImg();
		G.DrawImage(img,
			(int)position.x, (int)position.y, width, height);
	}

	}
}

