#pragma once
#include "Object.h"

class Texture;
class CameraUpButton : public Object
{
private:
	Texture* m_texture;
	bool		m_isOnWork;
	float		m_time;

public:
	virtual void update();
	virtual void render(HDC _dc, Graphics* _graphic);
	virtual void onMouseClicked();

public:
	CameraUpButton();
	~CameraUpButton();
};

