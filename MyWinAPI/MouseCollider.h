#pragma once

#include "cv.h"
class Object;

/// <summary>
/// 오브젝트가 마우스 입력을 감지할 수 있도록 하는 컴포넌트 클래스
/// </summary>
class MouseCollider
{

///맴버 변수
private:
	static UINT	m_idIndex;

	UINT m_id; //collider의 id정보
	Object*	m_owner; //collider를 소유하고 있는 오브젝트
	Vector2	m_size;	//충돌체의 크기 정보
	Vector2	m_fianlPos;	//collider의 

	//있을수도 있고 없을 수도 있는 것, 없으면 상자로 충돌 처리
	Mat m_imgCollider;//이미지 데이터


/// 맴버 함수
public:
	void		finalUpdate();

	UINT		getID()							{ return m_id; }

	void		setSize(Vector2 _size)			{ m_size = _size; }
	Vector2		getSize()						{ return m_size; }
	Vector2		getFianlPos()					{ return m_fianlPos; }
	Mat			getImgCollider()				{ return m_imgCollider; }
	Object*		getOwner()						{ return m_owner; }

	void		createImgCollider(Mat _img)		{ m_imgCollider = _img; }
	uchar		getPixelData(int _x, int _y)	{ return m_imgCollider.at<uchar>(_x, _y); }
	

///생성자와 소멸자
	MouseCollider();
	~MouseCollider();

	friend class Object;
};
