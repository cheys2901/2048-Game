#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vector>
#include <map>
#include <string>

using namespace std;

#include "ImageManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "MyUtil.h"
#include "SceneManager.h"
#include "ScoreManager.h"

using namespace MyUtil;

#define SAFEDELETE(p) if(p){delete(p); (p)= nullptr;}
#define IMAGEMANAGER ImageManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define INPUT InputManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()

#define WINSIZEX 570
#define WINSIZEY 700
#define WINSTARTX 400
#define WINSTARTY 100
#define WINNAME (LPSTR)(TEXT("2048"))
#define WINICON (LPSTR)(TEXT("icon.png"))
#define WINSTYLE WS_SYSMENU | WS_MINIMIZEBOX

extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;