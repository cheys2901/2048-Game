#include "stdafx.h"
#include "MainScene.h"

HRESULT MainScene::init()
{
	_offsetX = 0;
	_offsetY = 0;

	_start = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 100, 220, 74);
	_exit = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 200,220, 74);

	return S_OK;
}

void MainScene::release()
{
}

void MainScene::update()
{
	_offsetX++;
	_offsetY++;

	if (_offsetX > IMAGEMANAGER->findImage("mainBack")->getWidth())
	{
		_offsetX = 0;
	}
	if (_offsetY > IMAGEMANAGER->findImage("mainBack")->getHeight())
	{
		_offsetY = 0;
	}

	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_start, _ptMouse))
		{
			SCENEMANAGER->loadScene("playScene");
		}
		if (PtInRect(&_exit, _ptMouse))
		{
			PostQuitMessage(0);
		}
	}
}

void MainScene::render()
{
	HDC hdc = getMemDC();

	RECT rect = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->findImage("mainBack")->loopRender(hdc, &rect, _offsetX, _offsetY);

	HFONT font2048 = CreateFont(120, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, "Broadway");
	HFONT oFont = (HFONT)SelectObject(hdc, font2048);
	RECT textCell = RectMakeCenter(WINSIZEX / 2, 100, 50, 100);
	SetTextColor(hdc, RGB(0, 128, 0));
	SetBkMode(hdc, 1);
	DrawText(hdc, "2048", 4, &textCell, DT_CENTER | DT_NOCLIP | DT_EDITCONTROL);
	oFont = (HFONT)SelectObject(getMemDC(), oFont);
	DeleteObject(oFont);

	IMAGEMANAGER->findImage("startButton")->render(hdc, _start.left, _start.top);
	IMAGEMANAGER->findImage("exitButton")->render(hdc, _exit.left, _exit.top);
}
