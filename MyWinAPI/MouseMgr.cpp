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
	///���콺 ���� Ű�� �������� ��
	if (_keyManager->getKeyState(KEY::LBUTTON) == KEY_STATE::DOWN)
	{
		// ���콺 ��ǥ
		m_mousePos = Core::GetInstance()->getCursorPosC();


		//�˾� UI(����â ��ư)�� Ŭ���Ǿ����� Ȯ���Ѵ�.
		{
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI_SETTING);
			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 6;
				m_originUIPos = m_onFocusedObj->getPosition();
			}
		}


		//����â�� ���κ��� Ŭ���Ǿ����� Ȯ���Ѵ�. ( �ٸ� ������Ʈ ��ȣ�ۿ��� �����ؾ� �ϹǷ�...)
		if (m_onFocusedObj == nullptr)
		{
			//GROUP_TYPE::UI_DRAGABLE �� Ŭ���Ǿ����� Ȯ���Ѵ�. 
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI_SETTING_BG);
			
			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 5;
				m_originUIPos = m_onFocusedObj->getPosition();
				m_objName = m_onFocusedObj->Object::getName();
				/// ���� ����
				if (m_objName == L"homeButton")
				{
					SoundMgr::GetInstance()->playSFX((UINT)SOUND_SFX::OBJ_TAP);
				}
			}
		}

		if (m_onFocusedObj == nullptr)
		{
			//GROUP_TYPE::UI_DRAGABLE �� Ŭ���Ǿ����� Ȯ���Ѵ�. 
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

		//���� UI������ ������
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
			//GROUP_TYPE::OBJ_REACT�� Ŭ���Ǿ����� Ȯ���Ѵ�. 
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT);

			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 2;
				m_objName = m_onFocusedObj->Object::getName();
			}
		}

		if (m_onFocusedObj == nullptr)
		{
			//GROUP_TYPE::OBJ_REACT1�� Ŭ���Ǿ����� Ȯ���Ѵ�. 
			m_onFocusedObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT1);

			if (m_onFocusedObj != nullptr)
			{
				m_FocusedObjType = 7;
			}
		}


		m_prevMousePos = m_mousePos;
	}


	///���콺 ���� Ű�� ������ ���� ��
	if (_keyManager->getKeyState(KEY::LBUTTON) == KEY_STATE::HOLD)
	{
		//dx dy�� ���Ѵ�
		m_mousePos = Core::GetInstance()->getCursorPosC();

		m_dxdy.x = (float)(m_mousePos.x - m_prevMousePos.x);
		m_dxdy.y = (float)(m_mousePos.y - m_prevMousePos.y);


		if (m_FocusedObjType == 1) //
		{
			//������Ʈ �巡�� �۾��� �Ѵ�
			Vector2 UIPos = m_onFocusedObj->getPosition();
			m_onFocusedObj->setPosition(UIPos + m_dxdy);
		}
		else if (m_FocusedObjType == 4) // �κ��丮�� ��
		{
			float addOffSet = 0.f;
			if (m_inventoryOffset + m_dxdy.y < -1 && MIN_INVENTORY_OFFSET < m_inventoryOffset + m_dxdy.y)
			{
				addOffSet = m_dxdy.y;
				m_inventoryOffset += m_dxdy.y;

			}

			///�κ��丮 �κ� 
			Scene* curScene = SceneMgr::GetInstance()->getCurrentScene();
			const vector<Object*>& inventoryBar = curScene->GetGroupObject(GROUP_TYPE::INVENTORY_BG);
			for (auto obj : inventoryBar)
			{
				Vector2 pos = obj->getPosition();
				pos.y = pos.y + addOffSet;
				obj->setPosition(pos);
			}

			///�κ��丮 ������ �κ� 
			const vector<Object*>& inventoryItem = curScene->GetGroupObject(GROUP_TYPE::UI_DRAGABLE);
			for (auto obj : inventoryItem)
			{
				Vector2 pos = obj->getPosition();
				pos.y = pos.y + addOffSet;
				obj->setPosition(pos);
			}

			//����� ������ ǥ��
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
			//offset�� ����� �̵��� �����Ѵ�.
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


			//�ݺ��� ���鼭 ��� ������Ʈ�� addOffset�۾��� ���ش� <-virtual function
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



	///���콺 ���� Ű�� ���� ��
	if (_keyManager->getKeyState(KEY::LBUTTON) == KEY_STATE::UP)
	{
		m_dxdy.x = 0;
		m_dxdy.y = 0;

		if (m_FocusedObjType == 1) //���õ� ���� UI���� ��,
		{
			if (m_mousePos.x < 190) //UI�����̶��, ��ĥ �� �ִ� ������Ʈ�� ã�´�.
			{
				m_secondObj = MouseMgr::GetInstance()->checkSecondCollision(GROUP_TYPE::UI_DRAGABLE, m_onFocusedObj);
				if (m_secondObj != nullptr)
				{
					//��ȣ�ۿ��� �Ѵ�.
					m_onFocusedObj->onMouseCollision(m_secondObj);
					m_secondObj->onMouseCollision(m_onFocusedObj);
				}
			}
			else //�浹 ������ ������Ʈ�� ã�´�.
			{
				m_secondObj = MouseMgr::GetInstance()->checkSecondCollision(GROUP_TYPE::OBJ_REACT, m_onFocusedObj);
				if (m_secondObj != nullptr)
				{
					//��ȣ�ۿ��� �Ѵ�.
					m_onFocusedObj->onMouseCollision(m_secondObj);
					m_secondObj->onMouseCollision(m_onFocusedObj);
				}
				else //react���� ���� ã��, 1���� �ѹ� ��ã�´�.
				{
					m_secondObj = MouseMgr::GetInstance()->checkSecondCollision(GROUP_TYPE::OBJ_REACT1, m_onFocusedObj);
					if (m_secondObj != nullptr)
					{
						//��ȣ�ۿ��� �Ѵ�.
						m_onFocusedObj->onMouseCollision(m_secondObj);
						m_secondObj->onMouseCollision(m_onFocusedObj);
					}
				}
			}
			m_onFocusedObj->setPosition(m_originUIPos);
		}

		else if (m_FocusedObjType == 2) //���õ� ���� ������Ʈ���� ��,
		{
			//���� ������ �����Ѵ�.
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT);
			if (m_secondObj == m_onFocusedObj)
			{
				//������Ʈ�� Ŭ�� �̺�Ʈ�� �����Ѵ�.
				m_onFocusedObj->onMouseClicked();
			}
		}

		else if (m_FocusedObjType == 7) //���õ� ���� ������Ʈ���� ��,
		{
			//���� ������ �����Ѵ�.
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::OBJ_REACT1);
			if (m_secondObj == m_onFocusedObj)
			{
				//������Ʈ�� Ŭ�� �̺�Ʈ�� �����Ѵ�.
				m_onFocusedObj->onMouseClicked();
			}
		}


		else if (m_FocusedObjType == 3)//���õ� ���� ���� UI���� ��,
		{
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI);
			if (m_secondObj == m_onFocusedObj)
			{
				//������Ʈ�� Ŭ�� �̺�Ʈ�� �����Ѵ�.
				m_onFocusedObj->onMouseClicked();
			}
		}


		else if (m_FocusedObjType == 6)//���õ� ���� ����â ��ư�̾��� ��,
		{
			m_secondObj = MouseMgr::GetInstance()->checkCollision(GROUP_TYPE::UI_SETTING);
			if (m_secondObj == m_onFocusedObj)
			{
				//������Ʈ�� Ŭ�� �̺�Ʈ�� �����Ѵ�.
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
		//�浹ü�� �������� �ʴ� ��� (�׷� ���� ����� �ϱ⿡ ����ó�����ش�)
		//assert(objs[i]->getMouseCollider() != nullptr);
		if (objs[i]->getMouseCollider() == nullptr) continue;

		Vector2 colPos = objs[i]->getMouseCollider()->getFianlPos();
		Vector2 colSize = objs[i]->getMouseCollider()->getSize();

		if (colPos.x < (float)m_mousePos.x && (float)m_mousePos.x < colPos.x + colSize.x
			&& colPos.y < (float)m_mousePos.y && (float)m_mousePos.y < colPos.y + colSize.y)
		{
			//�浹ü�� �ڽ� �ݶ��̴��� ���
			if (objs[i]->getMouseCollider()->getImgCollider().empty())
			{
				//�浹 �ߴ�
				return objs[i];
			}
			else // �浹ü�� �̹��� �ݶ��̴��� ���
			{
				int x = m_mousePos.x - objs[i]->getPosition().x;
				int y = m_mousePos.y - objs[i]->getPosition().y;

				//opencv�� winapi�� ��ǥ ü�谡 �޶� �ݴ�� ��ǥ�� �Է��ؾ� �Ѵ�.
				int color = objs[i]->getMouseCollider()->getPixelData(y, x);
				if (color == 255)
				{
					//�浹 �ߴ�
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
		//�浹ü�� �������� �ʴ� ��� (�׷� ���� ����� �ϱ⿡ ����ó�����ش�)
		//assert(objs[i]->getMouseCollider() != nullptr);
		if (objs[i]->getMouseCollider() == nullptr) continue;

		//�ڱ� �ڽ��� ��� �����Ѵ�.
		if (objs[i] == _first) continue;

		Vector2 colPos = objs[i]->getMouseCollider()->getFianlPos();
		Vector2 colSize = objs[i]->getMouseCollider()->getSize();

		if (colPos.x < (float)m_mousePos.x && (float)m_mousePos.x < colPos.x + colSize.x
			&& colPos.y < (float)m_mousePos.y && (float)m_mousePos.y < colPos.y + colSize.y)
		{
			//�浹ü�� �ڽ� �ݶ��̴��� ���
			if (objs[i]->getMouseCollider()->getImgCollider().empty())
			{
				//�浹 �ߴ�
				return objs[i];
			}
			else // �浹ü�� �̹��� �ݶ��̴��� ���
			{
				int x = m_mousePos.x - objs[i]->getPosition().x;
				int y = m_mousePos.y - objs[i]->getPosition().y;

				//opencv�� winapi�� ��ǥ ü�谡 �޶� �ݴ�� ��ǥ�� �Է��ؾ� �Ѵ�.
				int color = objs[i]->getMouseCollider()->getPixelData(y, x);
				if (color == 255)
				{
					//�浹 �ߴ�
					return objs[i];
				}
			}
		}
	}
	return nullptr;
}