#pragma once
#include "Image.h"

class Scene
{
private:
	HDC _hdc;
public:
	Scene() {}
	virtual ~Scene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	LRESULT CALLBACK wndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	HDC getMemDC() { return IMAGEMANAGER->findImage("back")->getHDC(); }
	HDC getHDC() { return _hdc; }
};