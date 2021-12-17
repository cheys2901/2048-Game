#pragma once

class Timer
{
private:
	float _timeScale;
	float _timeElapsed;

	__int64 _curTime;
	__int64 _lastTime;

public:
	Timer();
	~Timer();

	HRESULT init();
	void tick(float lockFPS);
};

