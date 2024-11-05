#pragma once

class Animator;
class Texture;

/// <summary>
/// �ִϸ��̼��� �� ������ ������ ��� �ִ� ����ü
/// </summary>
struct AnimeFrameInfo 
{
	Vector2 leftTop;	//�������� �»�� ��
	Vector2 size;		//�� �������� ũ��
	float	speed;		//�� �������� ����� �ð�
};

/// <summary>
/// �ִϸ��̼� ������ ��� �ִ� Ŭ����
/// </summary>
class Animation
{

/// �ɹ� ����
private:
	wstring					m_name;
	Animator*				m_animator;			
	Texture*				m_texture;			//Animation�� ����ϴ� �ؽ���
	vector<AnimeFrameInfo>	m_frameInfos;		//��� ������ ����
	int						m_currentFrame;		//���� ������
	float					m_accumulatedTime;	//���� �ð�
	bool					m_isFinished;		//�ִϸ��̼� ����� �ѹ� �����°�


/// �ɹ� �Լ�
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



/// �����ڿ� �Ҹ���
	Animation();
	~Animation();

	friend class Animator;
};