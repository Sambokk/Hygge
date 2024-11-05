#include "pch.h"
#include "Texture.h"

#include "Core.h"

Texture::Texture()
	: m_hdc(0)
	, m_hBitMap(0)
	, m_bitMap{}
	, m_img(nullptr)
{

}

Texture::~Texture()
{
	DeleteDC(m_hdc);
	DeleteObject(m_hBitMap);
	delete(m_img);
}

void Texture::load(const wstring& _filePath)
{	
	//파일 로딩 후 비트맵 생성
	//m_hBitMap = (HBITMAP)LoadImage(nullptr, _filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	//비트맵과 연결할 DC 생성
	//m_hdc =	CreateCompatibleDC(Core::GetInstance()->getMainDC());

	// 비트맵과 DC 연결
	//HBITMAP hPrecBit = (HBITMAP)SelectObject(m_hdc, m_hBitMap);
	//DeleteObject(hPrecBit);

	//이미지 로딩
	m_img = new Image(_filePath.c_str());
}
