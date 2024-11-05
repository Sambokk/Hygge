#pragma once

#include "pch.h"
#include "function.h"
#include "EventMgr.h"
#include "Object.h"


/// <summary>
/// 객체를 생성하는 이벤트를 발생 시킨다.
/// </summary>
/// <param name="_obj">객체의 주소</param>
/// <param name="_type">객체의 종류</param>
void instantiate(Object* _obj, GROUP_TYPE _type)
{
	Event event = { };
	event.eventType = EVENT_TYPE::CREATE_OBJECT;
	event.lParam = (DWORD_PTR)_obj;
	event.wParam = (DWORD_PTR)_type;

	EventMgr::GetInstance()->addEvent(event);
}

/// <summary>
/// 객체를 제거하는 이벤트를 발생 시킨다.
/// </summary>
/// <param name="_obj">객체의 주소</param>
void destroy(Object* _obj)
{
	Event event = { };
	event.eventType = EVENT_TYPE::DELETE_OBJECT;
	event.lParam = (DWORD_PTR)_obj;

	EventMgr::GetInstance()->addEvent(event);
}

/// <summary>
/// Scene 변경을 나타내는 이벤트 발생
/// </summary>
/// <param name="_nextScene">씬 종류</param>
void changeScene(SCENE_TYPE _nextScene)
{
	Event event = { };
	event.eventType = EVENT_TYPE::SCENE_CHANGE;
	event.lParam = (DWORD_PTR)_nextScene;

	EventMgr::GetInstance()->addEvent(event);
}

