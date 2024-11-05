#include "pch.h"
#include "MouseMgr.h"

#include "KeyMgr.h"
#include "Core.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "MouseCollider.h"
#include "Object.h"
#include "SoundMgr.h"


MouseMgr::MouseMgr()
	:m_mousePos{}, m_prevMousePos{}, m_onFocusedObj(nullptr), m_FocusedObjType(0), m_secondObj(nullptr), m_originUIPos{}
{

}

MouseMgr::~MouseMgr()
{

}

void MouseMgr::update(KeyMgr* _keyManager)
{
	///마우스 왼쪽 키가 눌러졌을 때
	if (_keyManager->getKeyState(KEY::LBUTTON) == KEY_STATE::DOWN)
	{
		// 마우스 좌표
		m_mousePos = Core::GetInstance()->getCursorPosC();


		//팝업 UI(설정창 버튼)이 클릭되었는지 확인한다.
		{
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI_SETTING);
			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 6;
				m_originUIPos = m_onFocusedObj->getPosition();
			}
		}


		//설정창의 배경부분이 클릭되었는지 확인한다. ( 다른 오브젝트 상호작용을 무시해야 하므로...)
		if (m_onFocusedObj == nullptr)
		{
			//GROUP_TYPE::UI_DRAGABLE 가 클릭되었는지 확인한다. 
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI_SETTING_BG);
			
			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 5;
				m_originUIPos = m_onFocusedObj->getPosition();
				m_objName = m_onFocusedObj->Object::getName();
				/// 사운드 없음
				if (m_objName == L"homeButton")
				{
					SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
				}
			}
		}

		if (m_onFocusedObj == nullptr)
		{
			//GROUP_TYPE::UI_DRAGABLE 가 클릭되었는지 확인한다. 
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI_DRAGABLE);

			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 1;
				m_originUIPos = m_onFocusedObj->getPosition();
				//SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
			}
		}

		if (m_onFocusedObj == nullptr)
		{
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::INVENTORY_BG);

			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 4;
				//SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
			}
		}

		//우측 UI영역의 아이콘
		if (m_onFocusedObj == nullptr)
		{
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI);

			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 3;
				//SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_PICK);
			}
		}

		if (m_onFocusedObj == nullptr)
		{
			//GROUP_TYPE::OBJ_REACT가 클릭되었는지 확인한다. 
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT);

			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 2;
				m_objName = m_onFocusedObj->Object::getName();
			}
		}

		if (m_onFocusedObj == nullptr)
		{
			//GROUP_TYPE::OBJ_REACT1가 클릭되었는지 확인한다. 
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT1);

			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 7;
			}
		}


		m_prevMousePos = m_mousePos;
	}


	///마우스 왼쪽 키를 누르고 있을 때
	if (_keyManager->getKeyState(KEY::LBUTTON) == KEY_STATE::HOLD)
	{
		//dx dy를 구한다
		m_mousePos = Core::GetInstance()->getCursorPosC();

		m_dxdy.x = (float)(m_mousePos.x - m_prevMousePos.x);
		m_dxdy.y = (float)(m_mousePos.y - m_prevMousePos.y);


		if (m_FocusedObjType == 1) //
		{
			//오브젝트 드래그 작업을 한다
			Vector2 UIPos = m_onFocusedObj->getPosition();
			m_onFocusedObj->setPosition(UIPos + m_dxdy);
		}
		else if (m_FocusedObjType == 4) // 인벤토리일 떄
		{
			float addOffSet = 0.f;
			if (m_inventoryOffset + m_dxdy.y < -1 && MIN_INVENTORY_OFFSET < m_inventoryOffset + m_dxdy.y)
			{
				addOffSet = m_dxdy.y;
				m_inventoryOffset += m_dxdy.y;

			}

			///인벤토리 부분 
			Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
			const vector<Object*>& inventoryBar = curScene->GetGroupObject(GROUP_TYPE::INVENTORY_BG);
			for (auto obj : inventoryBar)
			{
				Vector2 pos = obj->getPosition();
				pos.y = pos.y + addOffSet;
				obj->setPosition(pos);
			}

			///인벤토리 아이템 부분 
			const vector<Object*>& inventoryItem = curScene->GetGroupObject(GROUP_TYPE::UI_DRAGABLE);
			for (auto obj : inventoryItem)
			{
				Vector2 pos = obj->getPosition();
				pos.y = pos.y + addOffSet;
				obj->setPosition(pos);
			}

			//사용한 아이템 표시
			const vector<Object*>& usedItem = curScene->GetGroupObject(GROUP_TYPE::UI_USED);
			for (auto obj : usedItem)
			{
				Vector2 pos = obj->getPosition();
				pos.y = pos.y + addOffSet;
				obj->setPosition(pos);
			}


		}
		else if (m_FocusedObjType == 0 || m_FocusedObjType == 2 || m_FocusedObjType == 7)
		{
			//offset을 벗어나는 이동은 무시한다.
			Vector2 addObjOffSet = { 0.f,0.f };
			if (m_xOffset + m_dxdy.x > -1 * MAX_XOFFSET && MAX_XOFFSET > m_xOffset + m_dxdy.x)
			{
				addObjOffSet.x = m_dxdy.x;
				m_xOffset += m_dxdy.x;
			}

			if (m_yOffset + m_dxdy.y > -1 * MAX_YOFFSET && MAX_YOFFSET > m_yOffset + m_dxdy.y)
			{
				addObjOffSet.y = m_dxdy.y;
				m_yOffset += m_dxdy.y;
			}


			//반복문 돌면서 모든 오브젝트의 addOffset작업을 해준다 <-virtual function
			Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
			const vector<Object*>& decoObjs = curScene->GetGroupObject(GROUP_TYPE::OBJ_REACT1);
			for (auto obj : decoObjs)
			{
				Vector2 pos = obj->getPosition();
				float depth = obj->getDepth();
				pos = pos + addObjOffSet * depth;
				obj->setPosition(pos);
			}


			const vector<Object*>& reactObjs = curScene->GetGroupObject(GROUP_TYPE::OBJ_REACT);
			for (auto obj : reactObjs)
			{
				Vector2 pos = obj->getPosition();
				float depth = obj->getDepth();
				pos = pos + addObjOffSet * depth;
				obj->setPosition(pos);
			}

			const vector<Object*>& bgObjs = curScene->GetGroupObject(GROUP_TYPE::OBJ_BG);
			for (auto obj : bgObjs)
			{
				Vector2 pos = obj->getPosition();
				float depth = obj->getDepth();
				pos = pos + addObjOffSet * depth;
				obj->setPosition(pos);
			}
		}
		m_prevMousePos = m_mousePos;
	}



	///마우스 왼쪽 키를 땠을 때
	if (_keyManager->getKeyState(KEY::LBUTTON) == KEY_STATE::UP)
	{
		m_dxdy.x = 0;
		m_dxdy.y = 0;

		if (m_FocusedObjType == 1) //선택된 것이 UI였을 때,
		{
			if (m_mousePos.x < 190) //UI영역이라면, 합칠 수 있는 오브젝트를 찾는다.
			{
				m_secondObj = MouseMgr::GetInstance()->checkSecondCollision(GROUP_TYPE::UI_DRAGABLE, m_onFocusedObj);
				if (m_secondObj != nullptr)
				{
					//상호작용을 한다.
					m_onFocusedObj->onMouseCollision(m_secondObj);
					m_secondObj->onMouseCollision(m_onFocusedObj);
				}
			}
			else //충돌 가능한 오브젝트를 찾는다.
			{
				m_secondObj = MouseMgr::GetInstance()->checkSecondCollision(GROUP_TYPE::OBJ_REACT, m_onFocusedObj);
				if (m_secondObj != nullptr)
				{
					//상호작용을 한다.
					m_onFocusedObj->onMouseCollision(m_secondObj);
					m_secondObj->onMouseCollision(m_onFocusedObj);
				}
				else //react에서 먼저 찾고, 1에서 한번 더찾는다.
				{
					m_secondObj = MouseMgr::GetInstance()->checkSecondCollision(GROUP_TYPE::OBJ_REACT1, m_onFocusedObj);
					if (m_secondObj != nullptr)
					{
						//상호작용을 한다.
						m_onFocusedObj->onMouseCollision(m_secondObj);
						m_secondObj->onMouseCollision(m_onFocusedObj);
					}
				}
			}
			m_onFocusedObj->setPosition(m_originUIPos);
		}

		else if (m_FocusedObjType == 2) //선택된 것이 오브젝트였을 때,
		{
			//같은 것인지 판정한다.
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT);
			if (m_secondObj == m_onFocusedObj)
			{
				//오브젝트의 클릭 이벤트를 수행한다.
				m_onFocusedObj->onMouseClicked();
			}
		}

		else if (m_FocusedObjType == 7) //선택된 것이 오브젝트였을 때,
		{
			//같은 것인지 판정한다.
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT1);
			if (m_secondObj == m_onFocusedObj)
			{
				//오브젝트의 클릭 이벤트를 수행한다.
				m_onFocusedObj->onMouseClicked();
			}
		}


		else if (m_FocusedObjType == 3)//선택된 것이 우측 UI였을 때,
		{
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI);
			if (m_secondObj == m_onFocusedObj)
			{
				//오브젝트의 클릭 이벤트를 수행한다.
				m_onFocusedObj->onMouseClicked();
			}
		}


		else if (m_FocusedObjType == 6)//선택된 것이 설정창 버튼이었을 때,
		{
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI_SETTING);
			if (m_secondObj == m_onFocusedObj)
			{
				//오브젝트의 클릭 이벤트를 수행한다.
				m_onFocusedObj->onMouseClicked();
			}
		}



		m_FocusedObjType = 0;
		m_onFocusedObj = nullptr;
		m_secondObj = nullptr;
	}
}

Object* MouseMgr::checkCollision(GROUP_TYPE _type)
{
	Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
	const vector<Object*>& objs = curScene->GetGroupObject(_type);

	for (int i = objs.size() - 1; 0 <= i; i--)
	{
		//충돌체를 보유하지 않는 경우 (그럴 일은 없어야 하기에 예외처리해준다)
		//assert(objs[i]->getMouseCollider() != nullptr);
		if (objs[i]->getMouseCollider() == nullptr) continue;

		Vector2 colPos = objs[i]->getMouseCollider()->getFianlPos();
		Vector2 colSize = objs[i]->getMouseCollider()->getSize();

		if (colPos.x < (float)m_mousePos.x && (float)m_mousePos.x < colPos.x + colSize.x
			&& colPos.y < (float)m_mousePos.y && (float)m_mousePos.y < colPos.y + colSize.y)
		{
			//충돌체가 박스 콜라이더인 경우
			if (objs[i]->getMouseCollider()->getImgCollider().empty())
			{
				//충돌 했다
				return objs[i];
			}
			else // 충돌체가 이미지 콜라이더인 경우
			{
				int x = m_mousePos.x - objs[i]->getPosition().x;
				int y = m_mousePos.y - objs[i]->getPosition().y;

				//opencv와 winapi의 좌표 체계가 달라 반대로 좌표를 입력해야 한다.
				int color = objs[i]->getMouseCollider()->getPixelData(y, x);
				if (color == 255)
				{
					//충돌 했다
					return objs[i];
				}
			}
		}
	}
	return nullptr;
}





Object* MouseMgr::checkSecondCollision(GROUP_TYPE _type, Object* _first)
{
	Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
	const vector<Object*>& objs = curScene->GetGroupObject(_type);

	for (int i = objs.size() - 1; 0 <= i; i--)
	{
		//충돌체를 보유하지 않는 경우 (그럴 일은 없어야 하기에 예외처리해준다)
		//assert(objs[i]->getMouseCollider() != nullptr);
		if (objs[i]->getMouseCollider() == nullptr) continue;

		//자기 자신일 경우 리턴한다.
		if (objs[i] == _first) continue;

		Vector2 colPos = objs[i]->getMouseCollider()->getFianlPos();
		Vector2 colSize = objs[i]->getMouseCollider()->getSize();

		if (colPos.x < (float)m_mousePos.x && (float)m_mousePos.x < colPos.x + colSize.x
			&& colPos.y < (float)m_mousePos.y && (float)m_mousePos.y < colPos.y + colSize.y)
		{
			//충돌체가 박스 콜라이더인 경우
			if (objs[i]->getMouseCollider()->getImgCollider().empty())
			{
				//충돌 했다
				return objs[i];
			}
			else // 충돌체가 이미지 콜라이더인 경우
			{
				int x = m_mousePos.x - objs[i]->getPosition().x;
				int y = m_mousePos.y - objs[i]->getPosition().y;

				//opencv와 winapi의 좌표 체계가 달라 반대로 좌표를 입력해야 한다.
				int color = objs[i]->getMouseCollider()->getPixelData(y, x);
				if (color == 255)
				{
					//충돌 했다
					return objs[i];
				}
			}
		}
	}
	return nullptr;
}