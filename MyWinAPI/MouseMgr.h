#pragma once

class KeyMgr;
class Object;
#define MAX_YOFFSET 100
#define MAX_XOFFSET 120
#define MIN_INVENTORY_OFFSET -1780


/// <summary>
/// 마우스 입력을 관리하는 매니저 클래스
/// </summary>
class MouseMgr
{
/// 맴버 변수
private:
	POINT m_mousePos;		//현재 마우스 위치
	POINT m_prevMousePos;	//이전 마우스 위치
	Vector2 m_originUIPos;	//충돌된 UI의 기존 위치

	Object* m_onFocusedObj;	//마우스를 눌렀을 때 충돌한 오브젝트
	int	 m_FocusedObjType;  // 0:none, 1:좌측UI, 2: obj2, 3:우측UI 4:인벤토리 5:설정창 6:설정창 버튼 7:obj1
	Object* m_secondObj;	//마우스를 올렸을 때 충돌한 오브젝트
	wstring m_objName;		// 특정 오브젝트의 이름을 저장하기 위한 변수

	Vector2 m_dxdy;			//시간당 마우스좌표 변화량 
	float	m_xOffset;		//추가된 x오프셋
	float	m_yOffset;		//추가된 y오프셋

	float m_inventoryOffset; // 인벤토리 y오프셋

/// 싱글톤 패턴 매크로
public:
	SINGLE(MouseMgr)

/// 맴버 함수 선언 
public:
	void update(KeyMgr* _keyManager);

private:
	Object* checkCollision(GROUP_TYPE _type);
	Object* checkSecondCollision(GROUP_TYPE _type, Object* _first);

/// 맴버 함수 정의와 선언
public:
	Vector2 getDxDy()		{ return m_dxdy; }
	Vector2 getMouseOffset(){ return Vector2(m_xOffset, m_yOffset); }
	
	float getInventoryOffset() { return m_inventoryOffset; }
	void setOffsetNormalState() { m_xOffset = 0; m_yOffset = 0; m_inventoryOffset = 0; }
};

