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
/// ������ : ���� �������� �ʱ�ȭ ���ݴϴ�.
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
/// �Ҹ��� : �ʱ�ȭ �� �� �Ҵ��ߴ� ���� �ڵ�� �� �� �귯���� �Ҵ����ݴϴ�
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
/// �����츦 �����ϰ�, ���� ���۸��� ���� ��Ʈ�ʰ� DC�� �����, �׸��� ��� �귯���� �����մϴ�.
/// </summary>
/// <param name="_hWnd">������ �ڵ�</param>
/// <param name="_resolution">������ �ػ�</param>
void Core::initialize(HWND _hWnd, POINT _resolution)
{	
	// �ܺο��� ���޹��� �Ű� �������� �ɹ� ������ �ű�ϴ�.
	m_hWnd = _hWnd;
	m_resolution = _resolution;

	// �ػ󵵿� �°� ������ ũ�⸦ �����մϴ�.
	RECT rt = { 0, 0, m_resolution.x, m_resolution.y };
	AdjustWindowRect(&rt, WS_POPUP | WS_CAPTION | WS_SYSMENU, FALSE); // �޴����� ũ�⸦ �����Ͽ� rt�� �ٽ� ���	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	SetWindowPos(_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� ����ϴ�.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_resolution.x, m_resolution.y);
	m_memoryDC = CreateCompatibleDC(m_hDC);
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memoryDC, m_hBit);
	DeleteObject(hOldBit);

	//�׷��Ƚ� ��ü�� �����մϴ�.
	m_graphic = new Graphics(m_memoryDC);

	// �� �� �귯���� �����մϴ�.
	createBrushPen();

	// �Ŵ��� Ŭ�������� �ʱ�ȭ ���ݴϴ�.
	PathMgr::GetInstance()->initialize();
	SoundMgr::GetInstance()->initialize();
	m_keyManager = new KeyMgr();
	SceneMgr::GetInstance()->initialize();
	TimeMgr::GetInstance()->initialize();
}

/// <summary>
/// ������ �����Ȳ�� ó���մϴ�.
/// </summary>
void Core::progress()
{
	/// ���콺 ������ ������Ʈ :
	GetCursorPos(&m_cursorPos);
	ScreenToClient(m_hWnd, &m_cursorPos);
	
	/// ���� ������Ʈ :
	// �Ŵ��� Ŭ�������� ������Ʈ ��ŵ�ϴ�.
	m_keyManager->update();
	TimeMgr::GetInstance()->update();
	MouseMgr::GetInstance()->update(m_keyManager);

	/// ���� ȭ�� ������Ʈ
	SceneMgr::GetInstance()->update(m_keyManager);

	/// ���� ȭ�� ������(���� ���۸��� �����)
	// �׸� ȭ�� ��ŭ �����
	//Rectangle(m_memoryDC, -1, -1, m_resolution.x + 1, m_resolution.y + 1);			// ȭ�� Ŭ����(���� �ػ󵵺��� 1 �� ū ũ���� �׸� �׸��鼭)
	SceneMgr::GetInstance()->render(m_memoryDC, m_graphic);							// ȭ�� ������
	BitBlt(m_hDC, 0, 0, m_resolution.x, m_resolution.y, m_memoryDC, 0, 0, SRCCOPY); // ������ �̹��� ���� �ֱ�
	
	TimeMgr::GetInstance()->render();

	/// �̺�Ʈ ���� ó��
	EventMgr::GetInstance()->update();

	///���� �Ŵ��� ������Ʈ
	SoundMgr::GetInstance()->update();
}

void Core::createBrushPen()
{
	brushes[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	pens[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	pens[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	pens[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
}
