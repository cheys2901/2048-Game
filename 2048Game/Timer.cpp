#include "stdafx.h"
#include "Timer.h"

#pragma comment(lib, "winmm.lib")

Timer::Timer() {}

Timer::~Timer() {}

HRESULT Timer::init()
{
	__int64 _periodFrequency;
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}

	return S_OK;
}

void Timer::tick(float lockFPS)
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed < 1.0f / lockFPS)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
}
