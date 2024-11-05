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
/// 모든 Scene 객체를 생성한 뒤, 시작 씬을 설정하고, 
/// 해당 Scene 필요한 초기화 작업을 수행합니다.
/// </summary>
void SceneMgr::initialize()
{
	// 모든 Scene 을 생성합니다.
	m_scenes[(UINT)SCENE_TYPE::TITLE] = new Scene_Start;
	m_scenes[(UINT)SCENE_TYPE::TITLE]->setName(L"Title Scene");

	// 추후 추가할 Scene
	// m_scenes[(UINT)SCENE_TYPE::RED] = new Scene_Red;
	// m_scenes[(UINT)SCENE_TYPE::RED]->setName(L"RED Scene");

	m_scenes[(UINT)SCENE_TYPE::BLUE] = new Scene_Blue;
	m_scenes[(UINT)SCENE_TYPE::BLUE]->setName(L"Blue Scene");

	// 추후 추가할 Scene
	// m_scenes[(UINT)SCENE_TYPE::GREEN] = new Scene_Green;
	// m_scenes[(UINT)SCENE_TYPE::GREEN]->setName(L"GREEN Scene");

	// 현재 Scene 지정 
	m_currentScene = m_scenes[(UINT)SCENE_TYPE::TITLE];
	m_currentScene->enter();
}

/// <summary>
/// 현재 Scene 업데이트 및 마지막 호출 확인
/// </summary>
void SceneMgr::update(KeyMgr* _keyManager)
{
	m_currentScene->update(_keyManager);
	m_currentScene->finalUpdate();
}

/// <summary>
/// 현재 Scene 랜더
/// </summary>
/// <param name="_dc">해당 씬을 그리기 위한 DC</param>
void SceneMgr::render(HDC _dc, Graphics* _graphic)
{
	m_currentScene->render(_dc, _graphic);
}

/// <summary>
/// 현재 Scene 을 다른 장면으로 바꿔줍니다.
/// </summary>
/// <param name="_next">바꿀 Scene</param>
void SceneMgr::changeScene(SCENE_TYPE _next)
{
	m_currentScene->exit();	// 씬을 닫으면서 일어나는 일들 
	m_currentScene = m_scenes[(UINT)_next]; //다른 씬으로 바꾼다
	m_currentScene->enter();
}

