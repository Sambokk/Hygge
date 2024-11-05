#pragma once
#include "Object.h"

class ItemMakeObject : public Object
{
private:
	// 새 아이템을 만들기 위한 속성
	wstring m_createItemName;
	wstring m_createItemKey;
	Vector2 m_createIteminagmePosition;
	Vector2 m_createIteminventoryPosition;

	wstring m_createIteminGameImagePath;
	string m_createIteminGamecvImagePath;
	wstring m_createItemOutGameImagePath;
	string m_createItemOutGamecvImagePath;

public:
	ItemMakeObject();

	ItemMakeObject(
		wstring _name, wstring _key, Vector2 _imagePosition, wstring _imagePath, string _cvImagePath, float _depth
		, wstring _createItemName, wstring _createItemKey, Vector2 _createIteminagmePosition, Vector2 _createIteminventoryPosition
		, wstring _createIteminGameImagePath, string _createIteminGamecvImagePath
		, wstring _createItemOutGameImagePath, string _createItemOutGamecvImagePath);

	~ItemMakeObject();

public:
	void update() override;
	void render(HDC _dc, Graphics* _graphic) override;
	void onMouseClicked() override;
};

