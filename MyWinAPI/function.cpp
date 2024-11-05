#pragma once

#include "pch.h"
#include "function.h"
#include "EventMgr.h"
#include "Object.h"


/// <summary>
/// ��ü�� �����ϴ� �̺�Ʈ�� �߻� ��Ų��.
/// </summary>
/// <param name="_obj">��ü�� �ּ�</param>
/// <param name="_type">��ü�� ����</param>
void instantiate(Object* _obj, GROUP_TYPE _type)
{
	Event event = { };
	event.eventType = EVENT_TYPE::CREATE_OBJECT;
	event.lParam = (DWORD_PTR)_obj;
	event.wParam = (DWORD_PTR)_type;

	EventMgr::GetInstance()->addEvent(event);
}

/// <summary>
/// ��ü�� �����ϴ� �̺�Ʈ�� �߻� ��Ų��.
/// </summary>
/// <param name="_obj">��ü�� �ּ�</param>
void destroy(Object* _obj)
{
	Event event = { };
	event.eventType = EVENT_TYPE::DELETE_OBJECT;
	event.lParam = (DWORD_PTR)_obj;

	EventMgr::GetInstance()->addEvent(event);
}

/// <summary>
/// Scene ������ ��Ÿ���� �̺�Ʈ �߻�
/// </summary>
/// <param name="_nextScene">�� ����</param>
void changeScene(SCENE_TYPE _nextScene)
{
	Event event = { };
	event.eventType = EVENT_TYPE::SCENE_CHANGE;
	event.lParam = (DWORD_PTR)_nextScene;

	EventMgr::GetInstance()->addEvent(event);
}

