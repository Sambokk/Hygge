#pragma once
#include "Object.h"


class Balloon : public Object
{
private:
	float m_time;


public:
	Balloon(wstring _name, wstring _key, Vector2 _pos, wstring _path, string _cvpath, float _depth);
	~Balloon();


public:
	virtual void update();
	virtual void render(HDC _dc, Graphics* _graphic);
	virtual void onMouseCollsion();
};

