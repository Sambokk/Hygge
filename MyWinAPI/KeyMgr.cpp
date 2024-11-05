#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"

int arrVK[(int)KEY::LAST] = {
	VK_ESCAPE,
	VK_LBUTTON,
	VK_OEM_3
};

KeyMgr::KeyMgr()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		keyInfos.push_back(KeyInfo{ KEY_STATE::NONE, false });
	}
}

KeyMgr::~KeyMgr()
{
}


void KeyMgr::update()
{
	//������ ��Ŀ�� �˾Ƴ���
	HWND hWnd = GetFocus();

	//�����찡 ��Ŀ�� ���� ��
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			//Ű�� �����ִ�.
			if (GetAsyncKeyState(arrVK[i]) & 0x8000)
			{
				if (keyInfos[i].isPreviousPush)
				{
					// �������� ���� �־���.
					keyInfos[i].state = KEY_STATE::HOLD;
				}
				else
				{
					keyInfos[i].state = KEY_STATE::DOWN;
				}
				keyInfos[i].isPreviousPush = true;
			}
			//Ű�� �������� �ʴ�.
			else
			{
				if (keyInfos[i].isPreviousPush)
				{
					keyInfos[i].state = KEY_STATE::UP;
				}
				else
				{
					keyInfos[i].state = KEY_STATE::NONE;
				}

				keyInfos[i].isPreviousPush = false;
			}
		}
	}

	//�����찡 ��Ŀ�� ���� �ƴ� ��,
	else
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			keyInfos[i].isPreviousPush = false;

			if (keyInfos[i].state == KEY_STATE::DOWN || keyInfos[i].state == KEY_STATE::HOLD)
			{
				keyInfos[i].state = KEY_STATE::UP;
				keyInfos[i].isPreviousPush = true;
			}
			else if (keyInfos[i].state == KEY_STATE::UP)
			{
				keyInfos[i].state = KEY_STATE::NONE;
				keyInfos[i].isPreviousPush = false;

			}
		}
	}
}