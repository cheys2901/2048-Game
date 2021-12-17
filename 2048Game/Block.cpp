#include "stdafx.h"
#include "Block.h"

HRESULT Block::init(int i, int j, int value)
{
	_x = 151 + (j * 90);
	_y = 281 + (i * 90);
	_rc = RectMakeCenter(_x, _y, 80, 80);
	_location = { j,i };
	_state = BLOCKMOVESTATE::BLOCK_IDLE;

	_offsetX = 0;
	_offsetY = 0;
	_isCombine = false;

	if (value != 0)
	{
		_value = value;
	}
	else
	{
		switch (GetRandom(10))
		{
		case 1:
			_value = 4;
			break;
		default:
			_value = 2;
			break;
		}
	}
	return S_OK;
}

void Block::release()
{
}

void Block::update()
{
	switch (_state)
	{
	case BLOCKMOVESTATE::BLOCK_MOVE_LEFT:
		_x -= 20;
		if (_x < 151 + (_location.x * 90))
		{
			_x = 151 + (_location.x * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_MOVE_RIGHT:
		_x += 20;

		if (_x > 151 + (_location.x * 90))
		{
			_x = 151 + (_location.x * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_MOVE_UP:
		_y -= 20;
		if (_y < 281 + (_location.y * 90))
		{
			_y = 281 + (_location.y * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_MOVE_DOWN:
		_y += 20;
		if (_y > 281 + (_location.y * 90))
		{
			_y = 281 + (_location.y * 90);
			_state = BLOCKMOVESTATE::BLOCK_IDLE;
		}
		break;
	case BLOCKMOVESTATE::BLOCK_IDLE:
		break;

	}
	_rc = RectMakeCenter(_x, _y, 80, 80);
}

void Block::render()
{
	string str = to_string(_value);
	IMAGEMANAGER->findImage(str)->renderCenter(getMemDC(), _x, _y);
}

void Block::setLocation(int i, int j)
{
	if (_location.x < j)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_RIGHT;
	}
	else if (_location.x > j)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_LEFT;
	}
	else if (_location.y < i)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_DOWN;
	}
	else if (_location.y > i)
	{
		_state = BLOCKMOVESTATE::BLOCK_MOVE_UP;
	}

	_location = { j,i };
}
