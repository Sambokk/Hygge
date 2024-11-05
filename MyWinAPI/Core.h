#pragma once

class KeyMgr;

/// <summary>
/// 게임의 핵심 로직을 처리하고, 그래픽 디바이스와 상호작용하여 게임의 그래픽을 출력합니다.
/// </summary>
class Core
{
private:
	POINT m_resolution;	// 해상도
	HWND m_hWnd; // 메인 윈도우 핸들
	HDC	m_hDC; // 메인 윈도우를 그릴 DC(Device Context)
	HBITMAP m_hBit;	// 비트맵 핸들
	Graphics* m_graphic; //gdi+ 그래픽스 객체
	HDC	m_memoryDC;	// 메모리 DC	

	HBRUSH	brushes[(UINT)BRUSH_TYPE::END];
	HPEN	pens[(UINT)PEN_TYPE::END];

	POINT	m_cursorPos;
	int		m_cameraOffset;	//카메라 오프셋 정보


	///매니저 객체
	KeyMgr* m_keyManager;

public:
	SINGLE(Core) // (싱글톤으로) 생성자 생성

public:
	void initialize(HWND _hWnd, POINT _resolution);
	void progress();

private:
	void createBrushPen();

public:
	HWND	getMainHwnd() { return m_hWnd; }
	HDC		getMainDC() { return m_hDC; }
	POINT	getResolution() { return m_resolution; }
	HBRUSH	getBrush(BRUSH_TYPE _type) { return brushes[(UINT)_type]; }
	HPEN	getPen(PEN_TYPE _type) { return pens[(UINT)_type]; }
	
	int   getCameraOffset()	{ return m_cameraOffset; }
	void	setCameraOffset(int _offset) { m_cameraOffset = _offset; };

	POINT	getCursorPosC() { return m_cursorPos; }
};

