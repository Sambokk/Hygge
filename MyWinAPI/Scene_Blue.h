#pragma once
#include "Scene.h"

class KeyMgr;

class Scene_Blue : public Scene
{
/// <summary>
/// 맴버 변수 선언
/// </summary>
private:


/// <summary>
/// 생성자와 소멸자
/// </summary>
public:
	Scene_Blue();
	~Scene_Blue();

/// <summary>
/// 맴버 변수
/// </summary>
public:


	virtual void update(KeyMgr* _keyManager);
	virtual void enter();
	virtual void exit();

	
};

