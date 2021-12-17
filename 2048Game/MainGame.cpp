#include "stdafx.h"
#include "MainGame.h"

HRESULT mainGame::init()
{
	Scene::init();
	imageInit();

	SCENEMANAGER->addScene("mainScene", new MainScene);
	SCENEMANAGER->addScene("playScene", new PlayScene);
	SCENEMANAGER->loadScene("mainScene");
	return S_OK;
}

void mainGame::release()
{
	Scene::release();
}

void mainGame::update()
{
	Scene::update();
	SCENEMANAGER->update();
}

void mainGame::render()
{
	RECT backRECT = { 0, 0, WINSIZEX, WINSIZEY };
	HBRUSH backBRSH = CreateSolidBrush(RGB(107, 223, 255));
	FillRect(getMemDC(), &backRECT, backBRSH);
	SCENEMANAGER->render();
	IMAGEMANAGER->findImage("back")->render(getHDC(), 0, 0);
}

void mainGame::imageInit()
{
	IMAGEMANAGER->addImage("mainBack", "Resource/mainBack.bmp", 800, 727, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("startButton", "Resource/startButton.bmp", 220, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("exitButton", "Resource/exitButton.bmp", 220, 74, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("result", "Resource/result.bmp", 400, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("newGameButton", "Resource/newGameButton.bmp", 150, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("overlay", "Resource/overlay.bmp", 370, 370, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("base", "Resource/base.bmp", 370, 370, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2", "Resource/2.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("4", "Resource/4.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("8", "Resource/8.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("16", "Resource/16.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("32", "Resource/32.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("64", "Resource/64.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("128", "Resource/128.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("256", "Resource/256.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("512", "Resource/512.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("1024", "Resource/1024.bmp", 80, 80, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("2048", "Resource/2048.bmp", 80, 80, false, RGB(255, 0, 255));
}
