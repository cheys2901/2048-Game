#include "stdafx.h"
#include "InputManager.h"

HRESULT InputManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyDown[i] = false;
	}
	return S_OK;
}

bool InputManager::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}
	return false;
}
