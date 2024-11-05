#pragma once
#include "Object.h"
#include "SoundMgr.h"

class Texture;
class SoundMgr;

class Item : public Object
{
private:
	Vector2 m_inventoryPosition;
	wstring m_outGameImagePath;
	string m_outGamecvImagePath;
	int m_sfxs;
	

public:
	Item();
	Item(wstring _name, wstring _key, Vector2 _inagmePosition, Vector2 _inventoryPosition, wstring _imagePath, string _cvImagePath, float _depth);
	Item(wstring _name, wstring _key, Vector2 _inagmePosition, Vector2 _inventoryPosition, 
		wstring _inGameImaigePath, string _inGamecvImagePath, 
		wstring _outGameImagePath, string _outGamecvImagePath,
		float _depth);

	Item(wstring _name, wstring _key, Vector2 _inagmePosition, Vector2 _inventoryPosition,
		wstring _inGameImaigePath, string _inGamecvImagePath,
		wstring _outGameImagePath, string _outGamecvImagePath,
		float _depth, int _sfxs);

	Item(wstring _name, wstring _key, Vector2 _inventoryPosition, wstring _imagePath);
	Item(wstring _name, wstring _key, Vector2 _inventoryPosition, wstring _imagePath, string _cvImagePath);

	~Item();
	
public:
	void update() override;
	void render(HDC _dc, Graphics* _graphic) override;

	void onMouseClicked() override;
	void onMouseCollision(Object*) override;


private:
	string pathToCvPAth(wstring _path);


};