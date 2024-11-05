#pragma once
#include "pch.h"

#include "Balloon.h"
#include "Texture.h"
#include "MouseCollider.h"
#include "TimeMgr.h"

Balloon::Balloon(wstring _name, wstring _key, Vector2 _pos, wstring _path, string _cvpath, float _depth)
	:m_time(0)
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
	threshold(myImg, myImg, 1, 255, THRESH_BINARY); //색상 값이 1 이상인 부분은 모두 255로 바꾸어준다.
	getMouseCollider()->createImgCollider(myImg);
	//imshow(_cvpath, myImg);
}

Balloon::~Balloon()
{

}

void Balloon::update()
{
	m_time += DeltaTime;
	if (3.f < m_time)
	{
		destroy(this);
	}
}

void Balloon::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight(); //(*texture).getHeigt()?
	Vector2 position = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)position.x, (int)position.y, width, height);
}

void Balloon::onMouseCollsion()
{	

}
