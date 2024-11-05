#include "pch.h"
#include "Inventory.h"

#include "Texture.h"
#include "Item.h"

#include "ResourceMgr.h"
#include "Scene.h"
#include "MouseCollider.h"

Inventory::Inventory()
	: m_items{}
{
	initialize(Vector2(0.f, 0.f), L"Inventory", L"texture\\ui_side_left.png");
	int width = getTexture()->getWidth();
	int height = getTexture()->getHeight();
	createMouseCollider();
	getMouseCollider()->setSize(Vector2((float)width, (float)height));

	/// 여기에 인벤토리에 미리 올려질 아이템을 넣어주세요 ///
}

Inventory::~Inventory()
{
	// 아이템 삭제
	for (Object* item : m_items)
	{
		//destroy(item);
	}
}

void Inventory::getItem(Object* _item, wstring _name, const wstring& _key, const wstring& _relativePath)
{

}

void Inventory::update()
{

}

void Inventory::render(HDC _dc, Graphics* _graphic)
{
	Texture* texture = getTexture();
	int width = texture->getWidth();
	int height = texture->getHeight();
	Vector2 inventoryPosition = getPosition();
	Image* img = texture->GetImg();
	_graphic->DrawImage(img, (int)inventoryPosition.x, (int)inventoryPosition.y, width, height);

	Vector2 itemPosition = Vector2(inventoryPosition.x, inventoryPosition.y + height + 10); // Item 출력 위치 설정

	// 아이템 출력
	for (Object* item : m_items)
	{
		//item->render(_dc, _graphic);
	}
}
