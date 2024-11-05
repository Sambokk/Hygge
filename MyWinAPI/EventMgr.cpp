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
	// m_remove에 저장한 객체들을 삭제
	for (size_t i = 0; i < m_remove.size(); i++)
	{
		delete m_remove[i];
	}
	m_remove.clear();
	
	// m_event에 저장한 이벤트들을 처리하기 위해 excute 함수 호출
	for (size_t i = 0; i < m_event.size(); i++)
	{
		excute(m_event[i]); // escute 함수로 이동
	}
	m_event.clear();
}

void EventMgr::excute(const Event& _event)
{
	//  switch 문을 사용하여 이벤트의 타입에 따라 적절한 동작을 수행
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
