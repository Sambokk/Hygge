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

///시간
#define DeltaTime			TimeMgr::GetInstance()->GetfDeltaTime()

//오브젝트 분류(유니티의 레이어 or 태그)
enum class GROUP_TYPE
{
	DEFAULT = 0,
		
	OBJ_BG,			// 게임 중앙의 배경 부분
	OBJ_REACT1,		// 게임 중앙의 상호작용 하지 않는 장식 오브젝트
	OBJ_REACT,		// 게임 중앙의 상호작용 가능한 오브젝트

	INVENTORY_BG,	// 인벤토리의 배경 부분(좌)
	UI_BG,			// 우측 UI 배경 부분

	UI,				// 우측의 클릭할 수 있는 UI 버튼
	UI_DRAGABLE,	// 좌측의 상호작용 가능한 UI 버튼
	UI_UNFOUND,		// 좌측의 아직 찾지 못한 UI
	UI_USED,		// 사용된 UI

	UI_SETTING_BG,	// ESC를 눌렀을 때 뜨는 UI의 창 
	UI_SETTING,		// ESC를 눌렀을 때 뜨는 설정 창의 버튼

	END = 32
};

enum class SCENE_TYPE
{
	TITLE,		// 첫 화면: Scene_Start
	BLUE,		// 첫 스테이지 : Scene_Blue
	RED,		/* 아직 만들지 않은 씬 */
	GREEN,

	END
};

// x 와 y 좌표를 갖는 구조체
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

	//포인터 구조체를 받기 위한
	Vector2& operator = (POINT _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vector2(const POINT& _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{ }

	//벡터 끼리의 연산
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
	HOLLOW, // 투명색
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