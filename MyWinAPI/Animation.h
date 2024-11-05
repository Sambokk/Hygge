#pragma once

class Animator;
class Texture;

/// <summary>
/// 애니매이션의 한 프레임 정보를 담고 있느 구조체
/// </summary>
struct AnimeFrameInfo 
{
	Vector2 leftTop;	//프레임의 좌상단 값
	Vector2 size;		//한 프레임의 크기
	float	speed;		//한 프레임을 출력할 시간
};

/// <summary>
/// 애니매이션 정보를 담고 있는 클래스
/// </summary>
class Animation
{

/// 맴버 변수
private:
	wstring					m_name;
	Animator*				m_animator;			
	Texture*				m_texture;			//Animation이 사용하는 텍스쳐
	vector<AnimeFrameInfo>	m_frameInfos;		//모든 프레임 정보
	int						m_currentFrame;		//현재 프레임
	float					m_accumulatedTime;	//누적 시간
	bool					m_isFinished;		//애니메이션 재생이 한번 끝났는가


/// 맴버 함수
private:
	void setName(const wstring& _name)	{ m_name = _name; }
	bool isAnimationFinished()			{ return m_isFinished; }



public:
	void update();
	void render(HDC _dc, Graphics* _graphic);
	void createAnimation(Texture* _texture, Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount);

	const wstring& getName()				{ return m_name; }

	void setFrame(int _frameIndex)
	{
		m_isFinished = false;
		m_currentFrame = _frameIndex;
		m_accumulatedTime = 0.f;
	}



/// 생성자와 소멸자
	Animation();
	~Animation();

	friend class Animator;
};