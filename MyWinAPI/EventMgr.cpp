#include "pch.h"

#include "EventMgr.h"
#include "SceneMgr.h"

#include "Object.h"
#include "Scene.h"

EventMgr::EventMgr()
{
}

EventMgr::~EventMgr()
{
}

void EventMgr::update()
{
	// m_remove�� ������ ��ü���� ����
	for (size_t i = 0; i < m_remove.size(); i++)
	{
		delete m_remove[i];
	}
	m_remove.clear();
	
	// m_event�� ������ �̺�Ʈ���� ó���ϱ� ���� excute �Լ� ȣ��
	for (size_t i = 0; i < m_event.size(); i++)
	{
		excute(m_event[i]); // escute �Լ��� �̵�
	}
	m_event.clear();
}

void EventMgr::excute(const Event& _event)
{
	//  switch ���� ����Ͽ� �̺�Ʈ�� Ÿ�Կ� ���� ������ ������ ����
	switch (_event.eventType)
	{
		case EVENT_TYPE::CREATE_OBJECT:
		{
			Object* newObject = (Object*)_event.lParam;
			GROUP_TYPE eventType = (GROUP_TYPE)_event.wParam;

			SceneMgr::GetInstance()->getCurrentScene()->addObject(newObject, eventType);
		}
			break;
		case EVENT_TYPE::DELETE_OBJECT:
		{
			Object* unactiveObject = (Object*)_event.lParam;
			unactiveObject->setRemove();
			m_remove.push_back(unactiveObject);
		}
			break;
		case EVENT_TYPE::SCENE_CHANGE:
		{
			SceneMgr::GetInstance()->changeScene((SCENE_TYPE)_event.lParam);
		}
			break;
		default:
			break;
	}
}
