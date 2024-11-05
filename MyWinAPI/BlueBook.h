#pragma once
#include "Object.h"

class BlueBook : public Object
{
private:
	Texture* m_texture;

	const int m_BookSize = 400;
	int m_filledBookSize;
	float m_fillingTime;
	float m_ChangingTime;
	bool m_isReadyToChangeSceneBlue;
	float m_alpha;

public:
	BlueBook(bool isFilled);
	~BlueBook();

public:
	virtual void update();
	virtual void render(HDC _dc, Graphics* _graphic);
	virtual void onMouseClicked();
};

