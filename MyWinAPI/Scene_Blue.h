#pragma once
#include "Scene.h"

class KeyMgr;

class Scene_Blue : public Scene
{
/// <summary>
/// �ɹ� ���� ����
/// </summary>
private:


/// <summary>
/// �����ڿ� �Ҹ���
/// </summary>
public:
	Scene_Blue();
	~Scene_Blue();

/// <summary>
/// �ɹ� ����
/// </summary>
public:


	virtual void update(KeyMgr* _keyManager);
	virtual void enter();
	virtual void exit();

	
};

