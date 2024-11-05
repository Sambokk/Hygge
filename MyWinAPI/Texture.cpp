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
	//���� �ε� �� ��Ʈ�� ����
	//m_hBitMap = (HBITMAP)LoadImage(nullptr, _filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	
	//��Ʈ�ʰ� ������ DC ����
	//m_hdc =	CreateCompatibleDC(Core::GetInstance()->getMainDC());

	// ��Ʈ�ʰ� DC ����
	//HBITMAP hPrecBit = (HBITMAP)SelectObject(m_hdc, m_hBitMap);
	//DeleteObject(hPrecBit);

	//�̹��� �ε�
	m_img = new Image(_filePath.c_str());
}
