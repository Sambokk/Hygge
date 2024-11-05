#include "pch.h"
#include "Fade_InOut.h"

#include "TimeMgr.h"

int Fade_InOut::m_lastColor = 0;

Fade_InOut::Fade_InOut(bool _isFadeIn)
	:m_isFadeIn(true), m_time(0), m_alpha(255), m_color(0), m_dAlpha(0)
{
	m_isFadeIn = _isFadeIn;
	if (m_isFadeIn)
	{
		m_alpha = 255;
		m_dAlpha = -15;
		m_color = m_lastColor;
	}
	else if(!m_isFadeIn)
	{
		m_alpha = 0;
		m_dAlpha = 15;
		m_color = 0;
	}
}

Fade_InOut::Fade_InOut(bool _isFadeIn, bool isWhite)
	:m_isFadeIn(true), m_time(0), m_alpha(255), m_color(255), m_dAlpha(0)
{
	m_isFadeIn = _isFadeIn;
	if (m_isFadeIn)
	{
		m_alpha = 255;
		m_dAlpha = -15;
		m_color = m_lastColor;
	}
	else if (!m_isFadeIn)
	{
		m_alpha = 0;
		m_dAlpha = 15;
		if (!isWhite) m_color = 0;
		m_lastColor = m_color;
	}
}


Fade_InOut::~Fade_InOut()
{

}

void Fade_InOut::update()
{
	
	//�ð��� ���� ���İ��� ���������ش�.
	m_time += DeltaTime;
	if (m_time > 0.03)
	{
		m_time -= 0.03;
		m_alpha += m_dAlpha;
	}

	// ���̵� ��/�ƿ� �۾��� �Ϸ�Ǹ� �� ������Ʈ�� �����Ѵ�.
	if (m_isFadeIn  && m_alpha == 0  ) destroy(this);
	if (!m_isFadeIn && m_alpha == 255) destroy(this);
}

void Fade_InOut::render(HDC _dc, Graphics* _grapics)
{
	SolidBrush b(Color((BYTE)m_alpha, m_color, m_color, m_color));
	_grapics->FillRectangle(&b, 0, 0, 1280, 720);
}


