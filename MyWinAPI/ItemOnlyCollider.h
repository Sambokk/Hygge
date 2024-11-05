#pragma once
#include "Object.h"

/// <summary>
/// �κ��丮�� ���� �ʰ� �浹 ���� ��ɸ� ������ �ΰ��� ������Ʈ ����
/// </summary>
class ItemOnlyCollider : public Object
{
/// �ɹ� ����
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

/// �����ڿ� �Ҹ���
public:
	ItemOnlyCollider(wstring _name, wstring _key, Vector2 _pos, wstring _path, string _cvpath, float _depth);
	~ItemOnlyCollider();


/// �ɹ� �Լ�
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

