#pragma once
#include "pch.h"

/// <summary>
/// 관리할 키를 담은 열거형
/// </summary>
enum class KEY
{
	ESC,
	LBUTTON,
	OEM_3,

	LAST
};
/// <summary>
/// 키 의 상태를 나타내는 열거형
/// </summary>
enum class KEY_STATE
{
	DOWN, //이전X 현재O
	HOLD, //이전O 현재O
	UP,   //이전O 현재X
	NONE, //이전X 현재X
};
/// <summary>
/// 키 상태 + 눌렸는지 여부
/// </summary>
struct KeyInfo
{
	KEY_STATE	state;			//키의 상태
	bool		isPreviousPush;	//이전에 눌렸는가?
};

class KeyMgr
{

/// 맴버 변수 선언
private:
	vector<KeyInfo> keyInfos;


/// 생성자와 소멸자
public:
	KeyMgr(); 
	~KeyMgr();;

/// 맴버 함수 선언
public:
	void update();


/// 맴버 함수 선언 및 정의
public:
	KEY_STATE getKeyState(KEY _key)
	{
		return keyInfos[(int)_key].state;
	}
};


