#include "stdafx.h"
#include "main.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse;
mainGame* mg;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWndSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_hInstance = hInstance;

	mg = new mainGame;

	WNDCLASS wnd;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wnd.hInstance = hInstance;
	wnd.lpfnWndProc = (WNDPROC)WndProc;
	wnd.lpszClassName = WINNAME;
	wnd.lpszMenuName = NULL;
	wnd.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wnd);

	_hWnd = CreateWindow(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTARTX,
		WINSTARTY,
		WINSIZEX,
		WINSIZEY,
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	setWndSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);
	ShowWindow(_hWnd, nCmdShow);

	mg->init();

	MSG msg;

	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	mg->release();
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return mg->wndProc(hWnd, iMessage, wParam, lParam);
}

void setWndSize(int x, int y, int width, int height)
{
	RECT wind;
	wind.left = 0;
	wind.right = width;
	wind.top = 0;
	wind.bottom = height;

	AdjustWindowRect(&wind, WINSTYLE, false);
	SetWindowPos(_hWnd, NULL, x, y, wind.right-wind.left, wind.bottom-wind.top, SWP_NOZORDER | SWP_NOMOVE);
}