#pragma once
#include "Object.h"

class Texture;
class MouseBubble : public Object
{
private:
	Texture* m_texture;
	float m_time;
	int m_lifeTime;
	
public:
	MouseBubble();
	~MouseBubble();


public:
	virtual void update();
};
