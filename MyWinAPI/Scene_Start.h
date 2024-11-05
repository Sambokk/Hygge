#pragma once
#include "Scene.h"

class KeyMgr;

class Scene_Start : public Scene
{
/// <summary>
/// �ɹ� ���� ����
/// </summary>
private:
	bool IsRedColored;
	bool IsBlueColored;
	bool IsGreenColored;

/// <summary>
/// �����ڿ� �Ҹ���
/// </summary>
public:
	Scene_Start();
	~Scene_Start();

/// <summary>
/// �ɹ� �Լ� 
/// </summary>
public:
	virtual void update(KeyMgr* _keyManager);
	virtual void enter();
	virtual void exit();
};

