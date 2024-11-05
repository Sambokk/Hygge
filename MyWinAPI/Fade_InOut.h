#pragma once


/// <summary>
/// �ڿ������� ȭ�� ��ȯ�� ���� �� ��ȯ�� ���� Ŭ����
/// </summary>
class Fade_InOut : public Object
{
/// �ɹ� ����
private:
	bool m_isFadeIn; //ȭ���� ���� ������°�?
	int m_alpha; //������ ���İ� ( 0�̸� ����, 255�̸� ������)
	int m_dAlpha; //���İ��� ��ȭ��
	float m_time;

	int m_color; //255 : ���, 0 : ����
	static int m_lastColor;

///�ɹ� �Լ�
public:
	virtual void update();
	virtual void render(HDC _dc, Graphics* _grapics);

///�����ڿ� �Ҹ���
public:
	Fade_InOut(bool _isFacdIn);
	Fade_InOut(bool _isFadeIn, bool isWhite);
	~Fade_InOut();
};

