#include "pch.h"
#include "Scene_Start.h"

// �߰��� ������Ʈ
#include "Object.h"
#include "Item.h"
#include "Book.h"
#include "UI.h"

#include "Core.h"

// �Ŵ���
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


	/// ESC �ٷ� ��� ���������̵�
	if (_keyManager->getKeyState(KEY::ESC) == KEY_STATE::DOWN) 
	{
		changeScene((SCENE_TYPE::BLUE)); // SceneMgr ���� ������ �Լ�
	}

	/// ` Ű ���� �ִ� å���� �����Ŵ
	if (_keyManager->getKeyState(KEY::OEM_3) == KEY_STATE::DOWN)
	{
		// Ư�� �׷� Ÿ�Կ� �ش��ϴ� ��ü�鿡 ���� �Լ� ����
		EventMgr::GetInstance()->SetRedBookClear();
		EventMgr::GetInstance()->SetBlueBookClear();
		EventMgr::GetInstance()->SetGreenBookClear();
	

		///����, �ʷ� å�� ���� �Ⱦ��� �ӽ÷� ���� �־�ѰԿ�
		// ����å
		if (!IsRedColored && EventMgr::GetInstance()->getIsRedBookClear())
		{
			Object* red_book = new Book(L"red_book", Vector2(190.f, 250.f), L"red_book", L"texture\\red_book.png");
			addObject(red_book, GROUP_TYPE::OBJ_REACT); // RedBook
			IsRedColored = true;
		}
		// �ʷ� å
		if (!IsGreenColored && EventMgr::GetInstance()->getIsGreenBookClear())
		{
			Object* green_book = new Book(L"GreenBookGray", Vector2(730.f, 205.f), L"green_book", L"texture\\green_book.png");
			addObject(green_book, GROUP_TYPE::OBJ_REACT); // GreenBook
			IsGreenColored = true;
		}
		// �Ķ� å
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
	SoundMgr::GetInstance()->playBGM((UINT)SOUND_BGM::TITLE); //�����

	//����â
	Object* settingButton = new UI(L"settingButton", Vector2(1150.f, 40.f), L"settingButton", L"texture\\ui_setting3.png" , (int)SCENE_TYPE::TITLE);
	addObject(settingButton, GROUP_TYPE::UI);

	Object* f = new Fade_InOut(true); // ȭ�� ��ȯ
	addObject(f, GROUP_TYPE::UI_SETTING_BG);

	Object* Title_Background = new Book(L"Title_Background", Vector2(0.f, 0.f), L"Title_Background", L"texture\\Title_Background.bmp"); // ���
	addObject(Title_Background, GROUP_TYPE::OBJ_BG);

	Object* title = new Book; // Ÿ��Ʋ
	title->initialize(Vector2(343.f, 30.f), L"title", L"texture\\title.png");
	addObject(title, GROUP_TYPE::OBJ_BG);

	Object* teamLogo = new Book; // �� �ΰ�
	teamLogo->initialize(Vector2(595.f, 635.f), L"teamLogo", L"texture\\Team_Pride_Loge_Text.png");
	addObject(teamLogo, GROUP_TYPE::OBJ_BG);

	Object* red_book_bw = new Book; // ����åGray
	red_book_bw->initialize(Vector2(190.f, 250.f), L"red_book_bw", L"texture\\red_book_bw.png");
	addObject(red_book_bw, GROUP_TYPE::OBJ_REACT);

	Object* green_book_bw = new Book; // �׸�ågray
	green_book_bw->initialize(Vector2(730.f, 205.f), L"green_book_bw", L"texture\\green_book_bw.png");
	addObject(green_book_bw, GROUP_TYPE::OBJ_REACT);

	Object* blue_book_bw = new Book(L"blueBook", Vector2(470.f, 210.f), L"blueBook", L"texture\\blue_book_bw.png"); // ���ågray
	addObject(blue_book_bw, GROUP_TYPE::OBJ_REACT);

	//�Ķ� å
	if ( !IsBlueColored && EventMgr::GetInstance()->getIsBlueBookClear() )
//	if(!IsBlueColored) å ������
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
	deleteAll(); // ��� ������Ʈ�� ����� (�θ𿡰� ��� ���� �Լ�)
}