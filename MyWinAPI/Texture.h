/// �̹��� �����͵��� ��� ��ü �Դϴ�.

#pragma once
#include "Res.h"

class Texture :
	public Res
{
/// <summary>
/// �ɹ� ����
/// </summary>
private:
	HDC			m_hdc;
	HBITMAP		m_hBitMap;
	BITMAP		m_bitMap;
	Image*		m_img;

/// <summary>
/// �����ڿ� �Ҹ���
/// </summary>
private:
	Texture();
	virtual ~Texture();

	friend class ResourceMgr; //���ҽ� �޴��������� texture �ν��Ͻ��� ������ �� �ִ�.
/// <summary>
/// �ɹ� �Լ� ����� ����
/// </summary>
public:
	void load(const wstring& _filePath);

	UINT	getWidth()	{ return m_img->GetWidth(); }
	UINT	getHeight() { return m_img->GetHeight(); }
	HDC		getDC()		{ return m_hdc; }
	Image*	GetImg()	{ return m_img; }
};

