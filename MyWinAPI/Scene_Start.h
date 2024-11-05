#pragma once
#include "Scene.h"

class KeyMgr;

class Scene_Start : public Scene
{
/// <summary>
/// 맴버 변수 선언
/// </summary>
private:
	bool IsRedColored;
	bool IsBlueColored;
	bool IsGreenColored;

/// <summary>
/// 생성자와 소멸자
/// </summary>
public:
	Scene_Start();
	~Scene_Start();

/// <summary>
/// 맴버 함수 
/// </summary>
public:
	virtual void update(KeyMgr* _keyManager);
	virtual void enter();
	virtual void exit();
};

