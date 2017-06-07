#include "stdafx.h"
#include <Windows.h>
#include <iostream>
#include "Math.h"


#ifdef _MSC_VER
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")
#endif

#ifndef _WINDOW_H
#define _WINDOW_H

class Window
{

public:

	bool _screenExit;
	bool _keyDown[256];
	HWND _hwnd;
	HDC _hdc;
	HBITMAP _hb;
	HBITMAP _ob;

public:

	_INT32 _screenWidth, _screenHeight;
	_PBYTE _screenBuffer;
	_LONG _screenPitch;
	LPTSTR _title;
	
public:

	Window();

	~Window();
	
	_INT32 Init(_INT32 width, _INT32 height, LPTSTR title);

	_INT32 Close();

	void Dispatch();

	void Update();

	void SetFPS(_INT32 fps);

public:

	LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static Window* g_window;


#endif