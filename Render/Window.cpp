#include "stdafx.h"
#include "Window.h"

Window::Window()
{
	_screenWidth = 0;
	_screenHeight = 0;
	_screenBuffer = NULL;
	_screenPitch = 0;
	memset(_keyDown, false, sizeof(bool) * 256);
	_screenExit = false;
	_hwnd = NULL;
	_hdc = NULL;
	_hb = NULL;
	_ob = NULL;
	g_window = this;
	_title = new TCHAR[512];
}

Window::~Window()
{
	delete[] _title;
}

_INT32 Window::Init(_INT32 width, _INT32 height, LPTSTR title)
{
	WNDCLASS wc;
	wc.style = CS_BYTEALIGNCLIENT;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = NULL;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = _T("SCREEN");

	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = width;
	bi.bmiHeader.biHeight = -height;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biSizeImage = width * height * 4;
	bi.bmiHeader.biXPelsPerMeter = 0;
	bi.bmiHeader.biYPelsPerMeter = 0;
	bi.bmiHeader.biClrUsed = 0;
	bi.bmiHeader.biClrImportant = 0;
	
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	Close();

	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClass(&wc))
	{
		return -1;
	}

	_hwnd = CreateWindow(_T("SCREEN"), title,
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wc.hInstance, NULL);
	if (_hwnd == NULL)
	{
		return -2;
	}

	_screenExit = false;

	HDC hDC = GetDC(_hwnd);
	_hdc = CreateCompatibleDC(hDC);
	ReleaseDC(_hwnd, hDC);

	_PVOID ptr;
	_hb = CreateDIBSection(_hdc, &bi, DIB_RGB_COLORS, &ptr, 0, 0);
	if (_hb == NULL)
	{
		return -3;
	}

	_ob = (HBITMAP)SelectObject(_hdc, _hb);
	_screenBuffer = (_PBYTE)ptr;
	_screenWidth = width;
	_screenHeight = height;
	_screenPitch = width * 4;
	lstrcpyW(_title, title);

	AdjustWindowRect(&rc, GetWindowLong(_hwnd, GWL_STYLE), 0);
	_INT32 wx = rc.right - rc.left;
	_INT32 wy = rc.bottom - rc.top;
	_INT32 sx = (GetSystemMetrics(SM_CXSCREEN) - wx) / 2;
	_INT32 sy = (GetSystemMetrics(SM_CYSCREEN) - wy) / 2;

	if (sy < 0)
	{
		sy = 0;
	}
	if (sx < 0)
	{
		sx = 0;
	}
	SetWindowPos(_hwnd, NULL, sx, sy, wx, wy, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));
	SetForegroundWindow(_hwnd);
	ShowWindow(_hwnd, SW_NORMAL);

	Dispatch();

	memset(_screenBuffer, 0, width * height * PTR_SIZE);

	return 0;
}

INT32 Window::Close()
{
	if (_hdc != NULL) 
	{
		if (_ob != NULL)
		{
			SelectObject(_hdc, _ob);
			_ob = NULL;
		}
		DeleteDC(_hdc);
		_hdc = NULL;
	}
	if (_hb != NULL)
	{
		DeleteObject(_hb);
		_hb = NULL;
	}
	if (_hwnd != NULL)
	{
		CloseWindow(_hwnd);
		_hwnd = NULL;
	}
	return 0;
}

void Window::Dispatch()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	while (_screenExit == false) 
	{
		if (!PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			break;
		}
		if (!GetMessage(&msg, NULL, 0, 0))
		{
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::Update()
{
	HDC hDC = GetDC(_hwnd);
	BitBlt(hDC, 0, 0, _screenWidth, _screenHeight, _hdc, 0, 0, SRCCOPY);
	ReleaseDC(_hwnd, hDC);
	Dispatch();
}

void Window::SetFPS(_INT32 fps)
{
	TCHAR _buffer[16];
	_itow_s(fps, _buffer, 10);
	std::wstring str;
	str.append(_title);
	str.append(_T(" FPS:"));
	str.append(_buffer);
	SetWindowText(_hwnd, str.data());
}

LRESULT CALLBACK Window::MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_KEYDOWN:
		{
			_keyDown[(_UINT32)wParam] = true;
			return 0;
		}
		case WM_KEYUP:
		{
			_keyDown[(_UINT32)wParam] = false;
			return 0;
		}
		default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
		{
			g_window->_screenExit = true;
			return 0;
		}
		case WM_CLOSE:
		{
			g_window->_screenExit = true;
			return 0;
		}
		default:
		{
			return g_window->MessageHandler(hWnd, uMsg, wParam, lParam);
		}
	}
	return 0;
}