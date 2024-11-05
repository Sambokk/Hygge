#pragma once


class Object;
class Animation;
class Texture;


/// <summary>
/// 오브젝트에서 애니매이션을 재생시킬 수 있는 컴포넌트 클래스
/// </summary>
class Animator
{
/// 맴버 변수
private:
	Animation*	m_currentAnimation;	//현재 재생중인 Animation
	map<wstring, Animation*> m_animations; //모든 Animation
	Object*	m_owner; //Animator를 소유한 오브젝트
	bool isRepeat; //반복 재생 여부

///맴버 함수
public:

	Object*		getObj() { return m_owner; }
	void		createAnimation(const wstring& _name, Texture* _texture, Vector2 _imgStartPos, Vector2 _cellSize, Vector2 _Step, float _speed, UINT _cellCount);
	Animation*	findAnimation(const wstring& _name);
	void		play(const wstring& _name, bool _repeat);

	void		render(HDC _dc, Graphics* _graphic);
	void		update();

///생성자와 소멸자
public:
	Animator();
	~Animator();


	friend class Object;
};