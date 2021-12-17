#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager() {}

TimeManager::~TimeManager() {}

HRESULT TimeManager::init()
{
	_timer = new Timer;
	_timer->init();

	return S_OK;
}

void TimeManager::release()
{
	if (_timer != NULL) SAFEDELETE(_timer);
}

void TimeManager::update(float lockFPS)
{
	if (_timer != NULL)
	{
		_timer->tick(lockFPS);
	}
}

void TimeManager::render(HDC hdc)
{
	char str[256];
	string frameRate;

	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
}