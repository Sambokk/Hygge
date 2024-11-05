#pragma once

#include <Windows.h>
#include <cassert>

#define SINGLE(type) public: \
    static type* GetInstance()\
	{ \
        static type manager; \
        return &manager; \
    } \
    private: \
        type(); \
        ~type();

///�ð�
#define DeltaTime			TimeMgr::GetInstance()->GetfDeltaTime()

//������Ʈ �з�(����Ƽ�� ���̾� or �±�)
enum class GROUP_TYPE
{
	DEFAULT = 0,
		
	OBJ_BG,			// ���� �߾��� ��� �κ�
	OBJ_REACT1,		// ���� �߾��� ��ȣ�ۿ� ���� �ʴ� ��� ������Ʈ
	OBJ_REACT,		// ���� �߾��� ��ȣ�ۿ� ������ ������Ʈ

	INVENTORY_BG,	// �κ��丮�� ��� �κ�(��)
	UI_BG,			// ���� UI ��� �κ�

	UI,				// ������ Ŭ���� �� �ִ� UI ��ư
	UI_DRAGABLE,	// ������ ��ȣ�ۿ� ������ UI ��ư
	UI_UNFOUND,		// ������ ���� ã�� ���� UI
	UI_USED,		// ���� UI

	UI_SETTING_BG,	// ESC�� ������ �� �ߴ� UI�� â 
	UI_SETTING,		// ESC�� ������ �� �ߴ� ���� â�� ��ư

	END = 32
};

enum class SCENE_TYPE
{
	TITLE,		// ù ȭ��: Scene_Start
	BLUE,		// ù �������� : Scene_Blue
	RED,		/* ���� ������ ���� �� */
	GREEN,

	END
};

// x �� y ��ǥ�� ���� ����ü
struct Vector2
{
	float x;
	float y;

public:
	Vector2()
		: x(0.f)
		, y(0.f)
	{ }

	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{ }

	Vector2(int _x, int _y)
		:x((float)_x)
		, y((float)_y)
	{ }

	//������ ����ü�� �ޱ� ����
	Vector2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vector2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{ }

	//���� ������ ����
	Vector2 operator + (Vector2 _otherV)
	{
		return Vector2(x + _otherV.x, y + _otherV.y);
	}

	Vector2 operator - (Vector2 _otherV)
	{
		return Vector2(x - _otherV.x, y - _otherV.y);
	}

	Vector2 operator * (Vector2 _otherV)
	{
		return Vector2(x * _otherV.x, y * _otherV.y);
	}

	Vector2 operator * (int _i)
	{
		return Vector2(x * _i, y * _i);
	}

	Vector2 operator * (float _i)
	{
		return Vector2(x * _i, y * _i);
	}

	Vector2 operator * (UINT _i)
	{
		return Vector2(x * _i, y * _i);
	}

	Vector2 operator / (Vector2 _otherV)
	{
		assert(!(_otherV.x == 0.f || _otherV.y == 0.f));
		return Vector2(x / _otherV.x, y / _otherV.y);
	}

};

enum class BRUSH_TYPE
{
	HOLLOW, // �����
	END
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,

	END
};

enum GAME_EVENT_TYPE
{
	NOTING,
	DEFAULT,
	UNDER,
	CLICK,
	MARGEABLE,
	FEED
};