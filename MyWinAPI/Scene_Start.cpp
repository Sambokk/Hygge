#include "pch.h"
#include "Scene_Start.h"

// 추가한 오브젝트
#include "Object.h"
#include "Item.h"
#include "Book.h"
#include "UI.h"

#include "Core.h"

// 매니저
#include "KeyMgr.h"
#include "Inventory.h"
#include "PathMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"
#include "EventMgr.h"
#include "Resource.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Fade_InOut.h"
#include "BlueBook.h"

Scene_Start::Scene_Start()
	: IsRedColored(false)
	, IsBlueColored(false)
	, IsGreenColored(false)
{
}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::update(KeyMgr* _keyManager)
{
	Scene::update(_keyManager);


	/// ESC 바로 블루 스테이지이동
	if (_keyManager->getKeyState(KEY::ESC) == KEY_STATE::DOWN) 
	{
		changeScene((SCENE_TYPE::BLUE)); // SceneMgr 에서 가져온 함수
	}

	/// ` 키 색깔 있는 책으로 변경시킴
	if (_keyManager->getKeyState(KEY::OEM_3) == KEY_STATE::DOWN)
	{
		// 특정 그룹 타입에 해당하는 객체들에 대해 함수 실행
		EventMgr::GetInstance()->SetRedBookClear();
		EventMgr::GetInstance()->SetBlueBookClear();
		EventMgr::GetInstance()->SetGreenBookClear();
	

		///빨간, 초록 책은 지금 안쓰니 임시로 여기 넣어둘게요
		// 빨간책
		if (!IsRedColored && EventMgr::GetInstance()->getIsRedBookClear())
		{
			Object* red_book = new Book(L"red_book", Vector2(190.f, 250.f), L"red_book", L"texture\\red_book.png");
			addObject(red_book, GROUP_TYPE::OBJ_REACT); // RedBook
			IsRedColored = true;
		}
		// 초록 책
		if (!IsGreenColored && EventMgr::GetInstance()->getIsGreenBookClear())
		{
			Object* green_book = new Book(L"GreenBookGray", Vector2(730.f, 205.f), L"green_book", L"texture\\green_book.png");
			addObject(green_book, GROUP_TYPE::OBJ_REACT); // GreenBook
			IsGreenColored = true;
		}
		// 파란 책
		if (!IsBlueColored && EventMgr::GetInstance()->getIsBlueBookClear())
		{
			Object* blue_book = new Book(L"BlueBook", Vector2(470.f, 210.f), L"BlueBook", L"texture\\blue_book.png");
			addObject(blue_book, GROUP_TYPE::OBJ_REACT); // BlueBook
			IsBlueColored = true;
		}
	}
}

void Scene_Start::enter()
{
	SoundMgr::GetInstance()->playBGM((UINT)SOUND_BGM::TITLE); //배경음

	//샛팅창
	Object* settingButton = new UI(L"settingButton", Vector2(1150.f, 40.f), L"settingButton", L"texture\\ui_setting3.png" , (int)SCENE_TYPE::TITLE);
	addObject(settingButton, GROUP_TYPE::UI);

	Object* f = new Fade_InOut(true); // 화면 전환
	addObject(f, GROUP_TYPE::UI_SETTING_BG);

	Object* Title_Background = new Book(L"Title_Background", Vector2(0.f, 0.f), L"Title_Background", L"texture\\Title_Background.bmp"); // 배경
	addObject(Title_Background, GROUP_TYPE::OBJ_BG);

	Object* title = new Book; // 타이틀
	title->initialize(Vector2(343.f, 30.f), L"title", L"texture\\title.png");
	addObject(title, GROUP_TYPE::OBJ_BG);

	Object* teamLogo = new Book; // 팀 로고
	teamLogo->initialize(Vector2(595.f, 635.f), L"teamLogo", L"texture\\Team_Pride_Loge_Text.png");
	addObject(teamLogo, GROUP_TYPE::OBJ_BG);

	Object* red_book_bw = new Book; // 빨간책Gray
	red_book_bw->initialize(Vector2(190.f, 250.f), L"red_book_bw", L"texture\\red_book_bw.png");
	addObject(red_book_bw, GROUP_TYPE::OBJ_REACT);

	Object* green_book_bw = new Book; // 그린책gray
	green_book_bw->initialize(Vector2(730.f, 205.f), L"green_book_bw", L"texture\\green_book_bw.png");
	addObject(green_book_bw, GROUP_TYPE::OBJ_REACT);

	Object* blue_book_bw = new Book(L"blueBook", Vector2(470.f, 210.f), L"blueBook", L"texture\\blue_book_bw.png"); // 블루책gray
	addObject(blue_book_bw, GROUP_TYPE::OBJ_REACT);

	//파란 책
	if ( !IsBlueColored && EventMgr::GetInstance()->getIsBlueBookClear() )
//	if(!IsBlueColored) 책 디버깅용
	{
		Object* bluebook = new BlueBook(false);
		bluebook->setPosition(Vector2(470.f, 210.f));
		addObject(bluebook, GROUP_TYPE::OBJ_REACT);
		IsBlueColored = true;
	}
	else if (IsBlueColored)
	{
		Object* bluebook = new BlueBook(true);
		bluebook->setPosition(Vector2(470.f, 210.f));
		addObject(bluebook, GROUP_TYPE::OBJ_REACT);
	}
}

void Scene_Start::exit()
{
	SoundMgr::GetInstance()->stopBGM();
	deleteAll(); // 모든 오브젝트를 지운다 (부모에게 상속 받은 함수)
}