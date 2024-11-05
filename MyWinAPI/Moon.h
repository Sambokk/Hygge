#pragma once

class Texture;

class Moon : public Object
{
private:
	wstring m_newItemName;
	wstring m_newItemKey;
	Vector2 m_newItemImagePosition;
	Vector2 m_newItemInventoryPosition;
	wstring m_newIteinGamePath;
	string m_newIteinGamecvImagePath;
	wstring m_newIteoutGamePath;
	string m_newIteoutGamecvePath;

	int m_clickNum;
	bool m_isGone;

public:
	Moon();

	Moon(wstring _name, wstring _key, Vector2 _imagePosition, wstring _imagePath,  string _cvImagePath // 달을 만들기 위한 매개 변수들
	, wstring _newItemName, wstring _newItemKeym, Vector2 _newItemImagePosition, Vector2 _newItemInventoryPosition // 달조각을 위한 매개 변수들
	, wstring _newIteinGamePath, string _newIteinGamecvImagePath, wstring _newIteoutGamePath, string _newIteoutGamecvePath
	, float _depth, int m_clickNum, bool _isGone
	);
	
	~Moon();

public:
	void update() override;
	void render(HDC _dc, Graphics* _graphic) override;
	void onMouseClicked() override;
	Vector2 adjustOffset(Vector2 _orginPos, float _depth);
};

