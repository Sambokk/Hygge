#pragma once

class KeyMgr;

/// <summary>
/// ������ �ٽ� ������ ó���ϰ�, �׷��� ����̽��� ��ȣ�ۿ��Ͽ� ������ �׷����� ����մϴ�.
/// </summary>
class Core
{
private:
	POINT m_resolution;	// �ػ�
	HWND m_hWnd; // ���� ������ �ڵ�
	HDC	m_hDC; // ���� �����츦 �׸� DC(Device Context)
	HBITMAP m_hBit;	// ��Ʈ�� �ڵ�
	Graphics* m_graphic; //gdi+ �׷��Ƚ� ��ü
	HDC	m_memoryDC;	// �޸� DC	

	HBRUSH	brushes[(UINT)BRUSH_TYPE::END];
	HPEN	pens[(UINT)PEN_TYPE::END];

	POINT	m_cursorPos;
	int		m_cameraOffset;	//ī�޶� ������ ����


	///�Ŵ��� ��ü
	KeyMgr* m_keyManager;

public:
	SINGLE(Core) // (�̱�������) ������ ����

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

