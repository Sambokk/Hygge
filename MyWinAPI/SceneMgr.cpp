#include "pch.h"
#include "SceneMgr.h"
#include "Scene_Start.h"
#include "Scene_Blue.h"

SceneMgr::SceneMgr()
	: m_scenes{}
	, m_currentScene(nullptr)
	, m_isRedBookClear(false)
	, m_isBlueBookClear(false)
	, m_isGreenBookClear(false)
{
}

SceneMgr::~SceneMgr()
{	
	for (int i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (m_scenes[i] == nullptr) continue;
		delete m_scenes[i];
	}
}

/// <summary>
/// ��� Scene ��ü�� ������ ��, ���� ���� �����ϰ�, 
/// �ش� Scene �ʿ��� �ʱ�ȭ �۾��� �����մϴ�.
/// </summary>
void SceneMgr::initialize()
{
	// ��� Scene �� �����մϴ�.
	m_scenes[(UINT)SCENE_TYPE::TITLE] = new Scene_Start;
	m_scenes[(UINT)SCENE_TYPE::TITLE]->setName(L"Title Scene");

	// ���� �߰��� Scene
	// m_scenes[(UINT)SCENE_TYPE::RED] = new Scene_Red;
	// m_scenes[(UINT)SCENE_TYPE::RED]->setName(L"RED Scene");

	m_scenes[(UINT)SCENE_TYPE::BLUE] = new Scene_Blue;
	m_scenes[(UINT)SCENE_TYPE::BLUE]->setName(L"Blue Scene");

	// ���� �߰��� Scene
	// m_scenes[(UINT)SCENE_TYPE::GREEN] = new Scene_Green;
	// m_scenes[(UINT)SCENE_TYPE::GREEN]->setName(L"GREEN Scene");

	// ���� Scene ���� 
	m_currentScene = m_scenes[(UINT)SCENE_TYPE::TITLE];
	m_currentScene->enter();
}

/// <summary>
/// ���� Scene ������Ʈ �� ������ ȣ�� Ȯ��
/// </summary>
void SceneMgr::update(KeyMgr* _keyManager)
{
	m_currentScene->update(_keyManager);
	m_currentScene->finalUpdate();
}

/// <summary>
/// ���� Scene ����
/// </summary>
/// <param name="_dc">�ش� ���� �׸��� ���� DC</param>
void SceneMgr::render(HDC _dc, Graphics* _graphic)
{
	m_currentScene->render(_dc, _graphic);
}

/// <summary>
/// ���� Scene �� �ٸ� ������� �ٲ��ݴϴ�.
/// </summary>
/// <param name="_next">�ٲ� Scene</param>
void SceneMgr::changeScene(SCENE_TYPE _next)
{
	m_currentScene->exit();	// ���� �����鼭 �Ͼ�� �ϵ� 
	m_currentScene = m_scenes[(UINT)_next]; //�ٸ� ������ �ٲ۴�
	m_currentScene->enter();
}

