#include <tchar.h>

#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"

TimeMgr::TimeMgr()
	: m_curCount{}
	, m_preCount{}
	, m_frequency{}
	, m_deltaTime(0.)
	, m_accumTime(0.)
	, m_callCount(0)
	, m_fps(0)
{
}

TimeMgr::~TimeMgr()
{
}

void TimeMgr::initialize()
{
	QueryPerformanceCounter(&m_curCount);		//���� ī��Ʈ
	QueryPerformanceFrequency(&m_frequency);	//�ʴ� ī��Ʈ Ƚ��
}

void TimeMgr::update()
{
	QueryPerformanceCounter(&m_curCount);

	//deltaTime ���
	m_deltaTime = ((double)m_curCount.QuadPart - m_preCount.QuadPart) / (double)m_frequency.QuadPart;
	m_preCount = m_curCount;
}

void TimeMgr::render()
{
// 	//fps ���
// 	m_callCount++;
// 	m_accumTime += m_deltaTime;
// 	if (m_accumTime >= 1.)
// 	{
// 		m_fps = m_callCount;
// 		m_accumTime = 0;
// 		m_callCount = 0;
// 
// 		wchar_t buffer[255] = {};
// 		swprintf_s(buffer, L"FPS : %d, DT : %lf, AcT : %lf", m_fps, m_deltaTime, m_accumTime);
// 		SetWindowText(Core::GetInstance()->getMainHwnd(), buffer);
// 	}
}
