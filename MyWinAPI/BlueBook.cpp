#pragma once
#include "pch.h"

#include "BlueBook.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "MouseCollider.h"
#include "ResourceMgr.h"
#include "Fade_InOut.h"
#include "SoundMgr.h"

BlueBook::BlueBook(bool isFilled)
	:m_fillingTime(0), m_isReadyToChangeSceneBlue(false), m_alpha(0)
{
	if (isFilled) m_filledBookSize = m_BookSize;
	else m_filledBookSize = 1;

	m_texture = ResourceMgr::GetInstance()->loadTexture(L"blue_book", L"texture\\blue_book.png");

	createMouseCollider();
	int width = m_texture->getWidth();
	int height = m_texture->getHeight();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));
}

BlueBook::~BlueBook()
{
}

void BlueBook::update()
{
// 	if (m_filledBookSize < m_BookSize)
// 	{
// 		m_fillingTime += DeltaTime;
// 		if (0.005f < m_fillingTime)
// 		{
// 			m_fillingTime -= 0.05f;
// 			m_filledBookSize++;
// 		}
// 	}

	if (m_alpha < 1.f)
	{
		m_fillingTime += DeltaTime;
		if (0.02f < m_fillingTime)
		{
			m_fillingTime -= 0.02f;
			m_alpha += 0.01f;
		}
	}


	if (m_isReadyToChangeSceneBlue)
	{
		m_ChangingTime += DeltaTime;
		if (m_ChangingTime > 0.5f) changeScene(SCENE_TYPE::BLUE);
	}
}

void BlueBook::render(HDC _dc, Gdiplus::Graphics* _graphic)
{
	int width = m_texture->getWidth();
	int height = m_texture->getHeight();
	Vector2 pos = getPosition();

	Image* img = m_texture->GetImg();


// 	Gdiplus::Rect destinationRect(pos.x, pos.y, width, m_filledBookSize);
// 	_graphic->DrawImage(
// 			img, 
// 			destinationRect, 
// 			0, 0, 
// 			width, m_filledBookSize, Gdiplus::UnitPixel);

	//이미지 알파 블랜딩
	ColorMatrix colorMatrix = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, m_alpha, 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
	ImageAttributes imageAtt;
	imageAtt.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault,
		ColorAdjustTypeBitmap);
	_graphic->DrawImage(
		img,
		Gdiplus::Rect(pos.x, pos.y, width, height),  // Destination rectangle
		0,                             // Source rectangle X 
		0,                             // Source rectangle Y
		width,                        // Source rectangle width
		height,                       // Source rectangle height
		UnitPixel,
		&imageAtt);
}

void BlueBook::onMouseClicked()
{
	SoundMgr::GetInstance()->playSFX(12);

	Object* f = new Fade_InOut(false);
	instantiate(f, GROUP_TYPE::UI_BG);

	m_isReadyToChangeSceneBlue = true;
}
