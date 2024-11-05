#pragma once
class Scene;

class KeyMgr;

class SceneMgr
{
/// <summary>
/// 맴버 변수 선언
/// </summary>
private:
	Scene* m_scenes[(UINT)SCENE_TYPE::END];		//모든 씬의 정보
	Scene* m_currentScene;						//현재 씬

	bool m_isRedBookClear;
	bool m_isBlueBookClear;
	bool m_isGreenBookClear;

/// <summary>
/// 싱글톤 패턴 매크로
/// </summary>
private:
	SINGLE(SceneMgr); 

/// <summary>
/// 맴버 함수 선언
/// </summary>
public:
	void initialize();
	void update(KeyMgr* _keyManager);
	void render(HDC _dc, Graphics* _graphic);
	void changeScene(SCENE_TYPE _next);

	bool getIsRedBookClear() { return m_isRedBookClear; }
	bool getIsBlueBookClear() { return m_isBlueBookClear; }
	bool getIsGreenBookClear() { return m_isGreenBookClear; }

	void SetRedBookClear() { m_isRedBookClear = true; }
	void SetBlueBookClear() { m_isBlueBookClear = true; }
	void SetGreenBookClear() { m_isGreenBookClear = true; }

private:
	Scene* getCurrentScene() { return m_currentScene; }
	friend class EventMgr;
	friend class MouseMgr;
	friend class CameraDownButton;
	friend class CameraUpButton;
	friend class UI;
	friend class ItemOnlyCollider;
/// <summary>
/// 맴버 함수의 선언과 정의
/// </summary>
public:
};

