#pragma once
#include "SingletonBase.h"
#define KEYMAX 256
class InputManager : public SingletonBase<InputManager>
{
private:
	bool _keyDown[KEYMAX];

public:
	InputManager() {}
	~InputManager() {}

	HRESULT init();

	bool GetKeyDown(int key);
};

