#pragma once

class Object;
class Item;



class Inventory : public Object
{
private:
	
	vector<Object*> m_items;
	vector<int> m_itemStates;	// ������ ���°� �迭

	float m_itemDistance = 0.f; // �迭 ��ġ ���� (�ӽ�)

public:
	Inventory();
	~Inventory();

// �� Obejct �� ���߿� �����ϱ�
public:
	void getItem(Object* _item, wstring _name, const wstring& _key, const wstring& _relativePath);

	void addItem(wstring _name, const wstring& _key, const wstring& _relativePath);

	virtual void update();
	virtual void render(HDC _dc, Graphics* _graphic);

};


