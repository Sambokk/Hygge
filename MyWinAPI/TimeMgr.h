#pragma once

class TimeMgr
{
	SINGLE(TimeMgr);

private:
	LARGE_INTEGER	m_curCount;
	LARGE_INTEGER	m_preCount;
	LARGE_INTEGER	m_frequency;

	double			m_deltaTime; //프레임 간의 시간 값
	double			m_accumTime;
	unsigned int	m_callCount; //초당 호출 수
	unsigned int	m_fps;

public:
	void initialize();
	void update();
	void render();

	double GetDeltaTime() { return m_deltaTime; }
	float   GetfDeltaTime() { return (float)m_deltaTime; }

};

