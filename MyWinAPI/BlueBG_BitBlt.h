#pragma once
#include "Object.h"

class Texture;

class BlueBG_BitBlt : public Object
{
private:

public:
	virtual void update() {}
	virtual void render(HDC _dc, Graphics* _graphic);

	BlueBG_BitBlt();
	~BlueBG_BitBlt();
};

