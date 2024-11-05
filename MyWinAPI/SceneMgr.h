#pragma once
class Scene;

class KeyMgr;

class SceneMgr
{
/// <summary>
/// �ɹ� ���� ����
/// </summary>
private:
	Scene* m_scenes[(UINT)SCENE_TYPE::END];		//��� ���� ����
	Scene* m_currentScene;						//���� ��

	bool m_isRedBookClear;
	bool m_isBlueBookClear;
	bool m_isGreenBookClear;

/// <summary>
/// �̱��� ���� ��ũ��
/// </summary>
private:
	SINGLE(SceneMgr); 

/// <summary>
/// �ɹ� �Լ� ����
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
/// �ɹ� �Լ��� ����� ����
/// </summary>
public:
};

