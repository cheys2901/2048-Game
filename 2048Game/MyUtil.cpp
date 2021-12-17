#include "stdafx.h"
#include "MyUtil.h"

RECT MyUtil::RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - width / 2,y - height / 2,x + width / 2,y + height / 2 };
	return rc;
}

RECT MyUtil::RectMake(int left, int top, int width, int height)
{
	RECT rc = { left, top,left + width,top + height };
	return rc;
}

int MyUtil::GetRandom(int num)
{
	return rand() % num;
}
