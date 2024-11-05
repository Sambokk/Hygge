/// 이미지 데이터들을 담는 객체 입니다.

#pragma once
#include "Res.h"

class Texture :
	public Res
{
/// <summary>
/// 맴버 변수
/// </summary>
private:
	HDC			m_hdc;
	HBITMAP		m_hBitMap;
	BITMAP		m_bitMap;
	Image*		m_img;

/// <summary>
/// 생성자와 소멸자
/// </summary>
private:
	Texture();
	virtual ~Texture();

	friend class ResourceMgr; //리소스 메니저에서만 texture 인스턴스를 생성할 수 있다.
/// <summary>
/// 맴버 함수 선언과 정의
/// </summary>
public:
	void load(const wstring& _filePath);

	UINT	getWidth()	{ return m_img->GetWidth(); }
	UINT	getHeight() { return m_img->GetHeight(); }
	HDC		getDC()		{ return m_hdc; }
	Image*	GetImg()	{ return m_img; }
};

