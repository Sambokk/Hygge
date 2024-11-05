#include "pch.h"
#include "Core.h"

#include "KeyMgr.h"
#include "EventMgr.h"
#include "PathMgr.h"
#include "SceneMgr.h"
#include "TimeMgr.h"
#include "MouseMgr.h"
#include "SoundMgr.h"

/// <summary>
/// 생성자 : 각종 변수들을 초기화 해줍니다.
/// </summary>
Core::Core()
	: m_hWnd(0)
	, m_resolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memoryDC(0)
	, brushes{}
	, pens{}
	, m_graphic(nullptr)
	, m_keyManager(nullptr)
{
}

/// <summary>
/// 소멸자 : 초기화 할 때 할당했던 각종 핸들과 펜 및 브러쉬를 할당해줍니다
/// </summary>
Core::~Core() 
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_memoryDC); 
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(pens[i]);
	}

	delete(m_graphic);
	delete(m_keyManager);
}

/// <summary>
/// 윈도우를 생성하고, 이중 버퍼링을 위한 비트맵과 DC를 만들고, 그리고 펜과 브러쉬를 생성합니다.
/// </summary>
/// <param name="_hWnd">윈도우 핸들</param>
/// <param name="_resolution">윈도우 해상도</param>
void Core::initialize(HWND _hWnd, POINT _resolution)
{	
	// 외부에서 전달받은 매개 변수들을 맴버 변수로 옮깁니다.
	m_hWnd = _hWnd;
	m_resolution = _resolution;

	// 해상도에 맞게 윈도우 크기를 조정합니다.
	RECT rt = { 0, 0, m_resolution.x, m_resolution.y };
	AdjustWindowRect(&rt, WS_POPUP | WS_CAPTION | WS_SYSMENU, FALSE); // 메뉴바의 크기를 감안하여 rt를 다시 계산	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 비트맵과 DC를 만듭니다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_resolution.x, m_resolution.y);
	m_memoryDC = CreateCompatibleDC(m_hDC);
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memoryDC, m_hBit);
	DeleteObject(hOldBit);

	//그래픽스 객체를 생성합니다.
	m_graphic = new Graphics(m_memoryDC);

	// 펜 및 브러쉬를 생성합니다.
	createBrushPen();

	// 매니저 클래스들을 초기화 해줍니다.
	PathMgr::GetInstance()->initialize();
	SoundMgr::GetInstance()->initialize();
	m_keyManager = new KeyMgr();
	SceneMgr::GetInstance()->initialize();
	TimeMgr::GetInstance()->initialize();
}

/// <summary>
/// 게임의 진행상황을 처리합니다.
/// </summary>
void Core::progress()
{
	/// 마우스 포지션 업데이트 :
	GetCursorPos(&m_cursorPos);
	ScreenToClient(m_hWnd, &m_cursorPos);
	
	/// 게임 업데이트 :
	// 매니저 클래스들을 업데이트 시킵니다.
	m_keyManager->update();
	TimeMgr::GetInstance()->update();
	MouseMgr::GetInstance()->update(m_keyManager);

	/// 게임 화면 업데이트
	SceneMgr::GetInstance()->update(m_keyManager);

	/// 게임 화면 랜더링(이중 버퍼링을 사용한)
	// 네모 화면 만큼 지우기
	//Rectangle(m_memoryDC, -1, -1, m_resolution.x + 1, m_resolution.y + 1);			// 화면 클리어(기존 해상도보다 1 더 큰 크기의 네모를 그리면서)
	SceneMgr::GetInstance()->render(m_memoryDC, m_graphic);							// 화면 랜더링
	BitBlt(m_hDC, 0, 0, m_resolution.x, m_resolution.y, m_memoryDC, 0, 0, SRCCOPY); // 랜더링 이미지 복사 넣기
	
	TimeMgr::GetInstance()->render();

	/// 이벤트 지연 처리
	EventMgr::GetInstance()->update();

	///사운드 매니저 업데이트
	SoundMgr::GetInstance()->update();
}

void Core::createBrushPen()
{
	brushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	pens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
}
