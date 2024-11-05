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
	//윈도우 포커싱 알아내기
	HWND hWnd = GetFocus();

	//윈도우가 포커싱 중일 때
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			//키가 눌려있다.
			if (GetAsyncKeyState(arrVK[i]) & 0x8000)
			{
				if (keyInfos[i].isPreviousPush)
				{
					// 이전에도 눌러 있었다.
					keyInfos[i].state = KEY_STATE::HOLD;
				}
				else
				{
					keyInfos[i].state = KEY_STATE::DOWN;
				}
				keyInfos[i].isPreviousPush = true;
			}
			//키가 눌려있지 않다.
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

	//윈도우가 포커싱 중이 아닐 때,
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