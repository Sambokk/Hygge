#pragma once


/// <summary>
/// 자연스러운 화면 전환을 위해 씬 전환시 사용될 클래스
/// </summary>
class Fade_InOut : public Object
{
/// 맴버 변수
private:
	bool m_isFadeIn; //화면이 점점 밝아지는가?
	int m_alpha; //색상의 알파값 ( 0이면 투명, 255이면 불투명)
	int m_dAlpha; //알파값의 변화량
	float m_time;

	int m_color; //255 : 흰색, 0 : 검정
	static int m_lastColor;

///맴버 함수
public:
	virtual void update();
	virtual void render(HDC _dc, Graphics* _grapics);

///생성자와 소멸자
public:
	Fade_InOut(bool _isFacdIn);
	Fade_InOut(bool _isFadeIn, bool isWhite);
	~Fade_InOut();
};

