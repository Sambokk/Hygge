#pragma once

#include "cv.h"
class Object;

/// <summary>
/// ������Ʈ�� ���콺 �Է��� ������ �� �ֵ��� �ϴ� ������Ʈ Ŭ����
/// </summary>
class MouseCollider
{

///�ɹ� ����
private:
	static UINT	m_idIndex;

	UINT m_id; //collider�� id����
	Object*	m_owner; //collider�� �����ϰ� �ִ� ������Ʈ
	Vector2	m_size;	//�浹ü�� ũ�� ����
	Vector2	m_fianlPos;	//collider�� 

	//�������� �ְ� ���� ���� �ִ� ��, ������ ���ڷ� �浹 ó��
	Mat m_imgCollider;//�̹��� ������


/// �ɹ� �Լ�
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
	

///�����ڿ� �Ҹ���
	MouseCollider();
	~MouseCollider();

	friend class Object;
};
