#pragma once
#include "SingletonBase.h"
#include "Timer.h"

class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* _timer;

public:
	TimeManager();
	~TimeManager();

	HRESULT init();
	void release();
	void update(float lockFPS = 0.0f);
	void render(HDC hdc);
};

