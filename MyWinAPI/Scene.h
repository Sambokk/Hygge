#pragma once
#include "pch.h"

/*
* Object Ŭ������ ��� ������ �Ű����� ������ ������� �ʰ�, �����ͷθ� ����ϰ� �ִ�. 
* �� ���, Object Ŭ������ ������ �ʿ������� ������ �ʿ����� �ʱ� ������, ���� ����
*/
class Object;
class KeyMgr;

class Scene
{
/// <summary>
/// �ɹ� ���� ����
/// </summary>
private:
	wstring	m_name;
	vector <Object*> m_objects[(UINT)GROUP_TYPE::END];

/// <summary>
/// �����ڿ� �Ҹ���
/// </summary>
public:
	Scene();
	virtual ~Scene();

/// <summary>
/// �ɹ� �Լ� ����
/// </summary>
public:
	void deleteObjectInGroup(GROUP_TYPE _targetGroup);
	void deleteAll();

/// <summary>
/// ���� �ɹ� �Լ� ����
/// </summary>
public:
	virtual void update(KeyMgr* _keyManager);
	virtual void finalUpdate();
	virtual void render(HDC _dc, Graphics* _grapics);

/// <summary>
/// �ɹ� �Լ� ����� ����
/// </summary>
public:
	void addObject(Object* _obj, GROUP_TYPE _type) { m_objects[(UINT)_type].push_back(_obj); }
	void setName(const wstring& _sceneName) { m_name = _sceneName; }
	const wstring& GetName() { return m_name; }
	virtual void enter() = 0; //�ش� ���� ���� �� ȣ��
	virtual void exit() = 0;  //�ش� ���� ���� �� ȣ��

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

