#include "stdafx.h"
#include "Scene.h"

HRESULT Scene::init()
{
	_hdc = GetDC(_hWnd);
	SetTimer(_hWnd, 1, 10, NULL);
	TIMEMANAGER->init();
	INPUT->init();
	IMAGEMANAGER->addImage("back", WINSIZEX, WINSIZEY);
	SCENEMANAGER->init();
	return S_OK;
}

void Scene::release()
{
	KillTimer(_hWnd, 1);
	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();
	INPUT->releaseSingleton();
	IMAGEMANAGER->releaseSingleton();
	SCENEMANAGER->release();
	SCENEMANAGER->releaseSingleton();
	ReleaseDC(_hWnd, _hdc);
}

void Scene::update()
{
	InvalidateRect(_hWnd, NULL, false);
	TIMEMANAGER->update(60);
}

void Scene::render()
{
}

LRESULT Scene::wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_ERASEBKGND:
		return (LRESULT)1;
	case WM_PAINT:
		this->render();
		break;
	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd,iMessage,wParam,lParam);
}
