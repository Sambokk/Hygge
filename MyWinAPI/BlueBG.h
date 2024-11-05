#pragma once
#include "Object.h"

class Texture;

class BlueBG : public Object
{
public:
	BlueBG();
	~BlueBG();

public:
	virtual void update() {};
	virtual void render(HDC _dc, Graphics* _graphic);
	virtual void initialize(Vector2 _position, const wstring& _key, const wstring& _relativePath);
};

