#pragma once


class Object;
class Animation;
class Texture;


/// <summary>
/// ������Ʈ���� �ִϸ��̼��� �����ų �� �ִ� ������Ʈ Ŭ����
/// </summary>
class Animator
{
/// �ɹ� ����
private:
	Animation*	m_currentAnimation;	//���� ������� Animation
	map<wstring, Animation*> m_animations; //��� Animation
	Object*	m_owner; //Animator�� ������ ������Ʈ
	bool isRepeat; //�ݺ� ��� ����

///�ɹ� �Լ�
public:

	Object*		getObj() { return m_owner; }
	void		createAnimation(const wstring& _name, Texture* _texture, Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount);
	Animation*	findAnimation(const wstring& _name);
	void		play(const wstring& _name, bool _repeat);

	void		render(HDC _dc, Graphics* _graphic);
	void		update();

///�����ڿ� �Ҹ���
public:
	Animator();
	~Animator();


	friend class Object;
};