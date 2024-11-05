// MyWinAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include "pch.h"

#include "framework.h"
#include "Core.h"
#include "Resource.h"


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;										// 현재 인스턴스입니다.
HWND hWnd;
WCHAR szTitle[MAX_LOADSTRING] = L"Hygge Hygge ~";       // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING] = L"WaWa";          // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE	 hInstance		// 현재 인스턴스 핸들
					, _In_opt_ HINSTANCE hPrevInstance  // 이전 인스턴스 핸들 (사용하지 않음)
					, _In_ LPWSTR		 lpCmdLine		// 명령줄 파라미터 (C 스타일 문자열)
					, _In_ int			 nCmdShow)		// 윈도우를 보여주는 방식 설정
{
	// 사용할 일 없는 wWinmain 함수의 매개변수가 가 초기화 하지 않았다는 메시지를 지운다.
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 메모리 누수 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 206; // 나중에 문제 생길 때 중단점 걸어줄 함수

	/// 윈도우 클래스 등록
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);					// 구조체의 크기

	wcex.style = CS_HREDRAW | CS_VREDRAW;				// 윈도우 클래스 스타일
	wcex.lpfnWndProc = WndProc;							// 윈도우 프로시저 함수의 포인터를 설정
	wcex.cbClsExtra = 0;								// 윈도우 클래스의 추가적인 메모리 공간을 설정 1
	wcex.cbWndExtra = 0;								// 윈도우 클래스의 추가적인 메모리 공간을 설정 2
	wcex.hInstance = hInstance;							// 윈도우 클래스의 인스턴스 핸들을 설정
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);		// 커서 핸들을 설정
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HEGGE_ICON));// 아이콘 핸들을 설정
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// 배경색을 설정
	wcex.lpszMenuName = NULL;							// 윈도우의 메뉴 이름을 설정
	wcex.lpszClassName = szWindowClass;					// 윈도우 클래스의 이름을 설정
	wcex.hIconSm = NULL;								// 작은 아이콘 핸들을 설정

	RegisterClassExW(&wcex);							// 지정된 설정을 사용하여 윈도우 클래스를 등록

	/// 애플리케이션 초기화를 수행합니다:

	// 인스턴스 핸들을 전역 변수에 저장합니다.
	// 인스턴스 핸들을 저장하고 주 창을 만듭니다.
	// 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
	// 주 프로그램 창을 만든 다음 표시합니다.
	hInst = hInstance;
	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
    MSG msg;


	///gdi+ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

	ULONG_PTR gpToken;

	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok)
	{
		MessageBox(NULL, TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."), TEXT("알림"), MB_OK);
		return 0;
	}

	///ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ


	/// 코어를 초기화
	Core::GetInstance()->initialize(hWnd, POINT{ 1280, 720 }); // 해상도 1280x720 // 해상도 1920x1080

    // 기본 메시지 루프입니다:
    while (1)
    {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			
			TranslateMessage(&msg);		// 키 입력 및 마우스 이벤트를 처리
			DispatchMessage(&msg);		// 윈도우 프로시저를 호출하여 해당 메시지를 처리
		}
		else
		{
			Core::GetInstance()->progress();
		}
    }

	///gdi+
	void GdiplusShutdown(ULONG_PTR token);

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_DESTROY:			// 윈도우가 파괴될 때 호출
		{
			PostQuitMessage(0);
			break;
		}
		case WM_CLOSE:
		{
			if (MessageBox(hWnd, L"정말 게임을 종료할건가요?", L"ㅠ_ㅠ" , MB_YESNO | MB_DEFBUTTON2) == IDYES)
			{
				PostQuitMessage(0); return 0;
			}
			break;
		}
		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
    }
    return 0;
}