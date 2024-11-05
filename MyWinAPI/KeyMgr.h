#pragma once
#include "pch.h"

/// <summary>
/// ������ Ű�� ���� ������
/// </summary>
enum class KEY
{
	ESC,
	LBUTTON,
	OEM_3,

	LAST
};
/// <summary>
/// Ű �� ���¸� ��Ÿ���� ������
/// </summary>
enum class KEY_STATE
{
	DOWN, //����X ����O
	HOLD, //����O ����O
	UP,   //����O ����X
	NONE, //����X ����X
};
/// <summary>
/// Ű ���� + ���ȴ��� ����
/// </summary>
struct KeyInfo
{
	KEY_STATE	state;			//Ű�� ����
	bool		isPreviousPush;	//������ ���ȴ°�?
};

class KeyMgr
{

/// �ɹ� ���� ����
private:
	vector<KeyInfo> keyInfos;


/// �����ڿ� �Ҹ���
public:
	KeyMgr(); 
	~KeyMgr();;

/// �ɹ� �Լ� ����
public:
	void update();


/// �ɹ� �Լ� ���� �� ����
public:
	KEY_STATE getKeyState(KEY _key)
	{
		return keyInfos[(int)_key].state;
	}
};


