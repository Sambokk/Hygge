#pragma once
#include "Object.h"

class StartBG 
	: public Object
{
/// <summary>
/// ��� ���� ����
/// </summary>
public:
	
/// <summary>
/// �����ڿ� �Ҹ���
/// </summary>
public:
	StartBG();
	~StartBG();

/// <summary>
/// �ɹ� �Լ��� ����
/// </summary>
public:
	

/// <summary>
/// ��ӹ��� ���� �Լ�
/// </summary>
public:
	virtual void update();
	virtual void render(HDC _dc);
};
