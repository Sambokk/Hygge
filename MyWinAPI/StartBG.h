#pragma once
#include "Object.h"

class StartBG 
	: public Object
{
/// <summary>
/// 멤버 변수 선언
/// </summary>
public:
	
/// <summary>
/// 생성자와 소멸자
/// </summary>
public:
	StartBG();
	~StartBG();

/// <summary>
/// 맴버 함수의 선언
/// </summary>
public:
	

/// <summary>
/// 상속받은 가상 함수
/// </summary>
public:
	virtual void update();
	virtual void render(HDC _dc);
};
