#pragma once

class KeyMgr;
class Object;
#define MAX_YOFFSET 100
#define MAX_XOFFSET 120
#define MIN_INVENTORY_OFFSET -1780


/// <summary>
/// ���콺 �Է��� �����ϴ� �Ŵ��� Ŭ����
/// </summary>
class MouseMgr
{
/// �ɹ� ����
private:
	POINT m_mousePos;		//���� ���콺 ��ġ
	POINT m_prevMousePos;	//���� ���콺 ��ġ
	Vector2 m_originUIPos;	//�浹�� UI�� ���� ��ġ

	Object* m_onFocusedObj;	//���콺�� ������ �� �浹�� ������Ʈ
	int	 m_FocusedObjType;  // 0:none, 1:����UI, 2: obj2, 3:����UI 4:�κ��丮 5:����â 6:����â ��ư 7:obj1
	Object* m_secondObj;	//���콺�� �÷��� �� �浹�� ������Ʈ
	wstring m_objName;		// Ư�� ������Ʈ�� �̸��� �����ϱ� ���� ����

	Vector2 m_dxdy;			//�ð��� ���콺��ǥ ��ȭ�� 
	float	m_xOffset;		//�߰��� x������
	float	m_yOffset;		//�߰��� y������

	float m_inventoryOffset; // �κ��丮 y������

/// �̱��� ���� ��ũ��
public:
	SINGLE(MouseMgr)

/// �ɹ� �Լ� ���� 
public:
	void update(KeyMgr* _keyManager);

private:
	Object* checkCollision(GROUP_TYPE _type);
	Object* checkSecondCollision(GROUP_TYPE _type, Object* _first);

/// �ɹ� �Լ� ���ǿ� ����
public:
	Vector2 getDxDy()		{ return m_dxdy; }
	Vector2 getMouseOffset(){ return Vector2(m_xOffset, m_yOffset); }
	
	float getInventoryOffset() { return m_inventoryOffset; }
	void setOffsetNormalState() { m_xOffset = 0; m_yOffset = 0; m_inventoryOffset = 0; }
};

