#pragma once

class Object;
class Item;



class Inventory : public Object
{
private:
	
	vector<Object*> m_items;
	vector<int> m_itemStates;	// 아이템 상태값 배열

	float m_itemDistance = 0.f; // 배열 배치 순서 (임시)

public:
	Inventory();
	~Inventory();

// 들어갈 Obejct 는 나중에 생각하기
public:
	void getItem(Object* _item, wstring _name, const wstring& _key, const wstring& _relativePath);

	void addItem(wstring _name, const wstring& _key, const wstring& _relativePath);

	virtual void update();
	virtual void render(HDC _dc, Graphics* _graphic);

};


