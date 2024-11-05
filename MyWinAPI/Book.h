#pragma once
#include "Object.h"

class Texture;

class Book : public Object
{
private:
	float m_time;
	bool m_isReadyToChangeSceneBlue;

public:
	Book();
	Book(wstring _name, Vector2 _position, wstring _key, wstring _path);
	~Book();

public:
	virtual void update();
	virtual void render(HDC _dc, Graphics* _graphic);
	virtual void initialize(Vector2 _position, const wstring& _key, const wstring& _relativePath);
	virtual void onMouseClicked();
};
