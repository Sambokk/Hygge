#pragma once
#include "Object.h"

/// <summary>
/// 인벤토리에 담지 않고 충돌 판정 기능만 가지는 인게임 오브젝트 유형
/// </summary>
class ItemOnlyCollider : public Object
{
/// 맴버 변수
private:
	static Vector2 m_cavePos;

	float m_nightingTime;
	bool m_isNight;
	bool m_isNightingEnd;
	bool m_isWitchSpawn;
	static bool m_isGameEnd;
	static bool m_isGameEndReal;

	bool m_isShipAbleToClick;
	bool m_isWitchAbleToClick;
	bool m_isMermaidAbleToClick;

	static float m_gameEndTime;
	float m_witchTime;
	float m_shipTime;
	float m_mermaidTime;
	float m_bubbleTime;

	int m_witchsCollectionCount;

/// 생성자와 소멸자
public:
	ItemOnlyCollider(wstring _name, wstring _key, Vector2 _pos, wstring _path, string _cvpath, float _depth);
	~ItemOnlyCollider();


/// 맴버 함수
public:
	void update() override;
	void render(HDC _dc, Graphics* _graphic) override;
	void onMouseClicked() override;
	void onMouseCollision(Object* _other) override;


private:
	void setNight();
	void createNightObject();
	Vector2 adjustOffset(Vector2 _orginPos, float _depth);
	void startEndingEvent();
};

