#pragma once
#include "pch.h"

/*
* Object 클래스를 멤버 변수나 매개변수 등으로 사용하지 않고, 포인터로만 사용하고 있다. 
* 이 경우, Object 클래스의 선언이 필요하지만 구현은 필요하지 않기 때문에, 전방 선언
*/
class Object;
class KeyMgr;

class Scene
{
/// <summary>
/// 맴버 변수 선언
/// </summary>
private:
	wstring	m_name;
	vector <Object*> m_objects[(UINT)GROUP_TYPE::END];

/// <summary>
/// 생성자와 소멸자
/// </summary>
public:
	Scene();
	virtual ~Scene();

/// <summary>
/// 맴버 함수 선언
/// </summary>
public:
	void deleteObjectInGroup(GROUP_TYPE _targetGroup);
	void deleteAll();

/// <summary>
/// 가상 맴버 함수 선언
/// </summary>
public:
	virtual void update(KeyMgr* _keyManager);
	virtual void finalUpdate();
	virtual void render(HDC _dc, Graphics* _grapics);

/// <summary>
/// 맴버 함수 선언과 정의
/// </summary>
public:
	void addObject(Object* _obj, GROUP_TYPE _type) { m_objects[(UINT)_type].push_back(_obj); }
	void setName(const wstring& _sceneName) { m_name = _sceneName; }
	const wstring& GetName() { return m_name; }
	virtual void enter() = 0; //해당 씬에 진입 시 호출
	virtual void exit() = 0;  //해당 씬을 나갈 시 호출

	const vector<Object*>& GetGroupObject(GROUP_TYPE _type) { return m_objects[(UINT)_type]; }
	
	template<typename Func>
	void executeFunctionOnGroupObjects(GROUP_TYPE _type, Func&& function)
	{
		for (Object* object : m_objects[(UINT)_type])
		{
			function(object);
		}
	}
};

