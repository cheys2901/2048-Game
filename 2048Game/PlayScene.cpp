#include "stdafx.h"
#include "PlayScene.h"

HRESULT PlayScene::init()
{
	_state = PLAYSCENESTATE::BLOCK_IDLE;
	_isCombine = false;
	_push = false;

	_newGame = RectMake(110, 160, 190, 40);
	initData(true);

	return S_OK;
}

void PlayScene::initData(bool isLoad) 
{
	// 0 - Best score
	// 1 - Current score
	// 2 - 16 - base
	int data[18];
	bool isReaded = ScoreManager::getSingleton()->loadData("userdata.save", data);

	if (isReaded)
	{
		if (isLoad) {
			_hightScore = data[0];
			_currentScore = data[1];
			int index = 2;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_base[i][j].rc = RectMakeCenter(151 + (j * 90), 281 + (i * 90), 80, 80);
					if (data[index] != 0)
					{
						_base[i][j].state = BASE_FULL;
						_base[i][j].value = data[index];
						Block* bl = new Block;
						bl->init(i, j, _base[i][j].value);
						_vBlock.push_back(bl);
					}
					else
					{
						_base[i][j].state = BASE_EMPTY;
						_base[i][j].value = 0;
					}
					index++;
				}
			}
		}
	}
	else
	{
		_hightScore = 0;
	}
	
	if (!isReaded || !isLoad)
	{
		_currentScore = 0;
		pushBlock();
		pushBlock();
	}
}

void PlayScene::release()
{
	int data[18];
	data[0] = _hightScore;
	data[1] = _currentScore;
	int index = 2;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			data[index] = _base[i][j].value;
			index++;
		}
	}
	ScoreManager::getSingleton()->saveData("userdata.save", data);

	ReleaseDC(_hWnd, getHDC());
}

void PlayScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_newGame, _ptMouse))
		{
			for (int i = 0; i < 4; i++) 
			{
				for (int j = 0; j < 4; j++) 
				{
					_base[i][j].state = BASE_EMPTY;
					_base[i][j].value = 0;
				}
			}
			_vBlock.clear();
			initData(false);
		}
	}

	for (int i = 0; i < _vBlock.size(); i++)
	{
		_vBlock[i]->update();
	}

	if (_currentScore > _hightScore) _hightScore = _currentScore;

	switch (_state)
	{
	case PLAYSCENESTATE::BLOCK_SET_LEFT:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{

			POINT temp = _vBlock[i]->getLocation();
			for (int j = 0; j < _vBlock[i]->getLocation().x; j++)
			{
				if (_base[temp.y][j].state == BASE_FULL)
				{
					count++;
				}

			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetX(count);
			count = 0;
		}

		_state = PLAYSCENESTATE::BLOCK_MOVE_LEFT;
		if (CheckOffsetX()) _push = true;
		else _push = false;

		break;
	case PLAYSCENESTATE::BLOCK_SET_RIGHT:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			for (int j = temp.x + 1; j < 4; j++)
			{
				if (_base[temp.y][j].state == BASE_FULL)
				{
					count++;
				}
			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetX(3 - count);
			count = 0;
		}


		_state = PLAYSCENESTATE::BLOCK_MOVE_RIGHT;
		if (CheckOffsetX()) _push = true;
		else _push = false;

		break;
	case PLAYSCENESTATE::BLOCK_SET_UP:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			for (int j = 0; j < _vBlock[i]->getLocation().y; j++)
			{
				if (_base[j][temp.x].state == BASE_FULL)
				{
					count++;
				}

			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetY(count);
			count = 0;
		}

		_state = PLAYSCENESTATE::BLOCK_MOVE_UP;
		if (CheckOffsetY()) _push = true;
		else _push = false;

		break;
	case PLAYSCENESTATE::BLOCK_SET_DOWN:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();

			for (int j = temp.y + 1; j < 4; j++)
			{
				if (_base[j][temp.x].state == BASE_FULL)
				{
					count++;
				}

			}
			if (_vBlock[i]->getIsCombine() == true) count--;
			_vBlock[i]->setOffsetY(3 - count);
			count = 0;
		}


		_state = PLAYSCENESTATE::BLOCK_MOVE_DOWN;
		if (CheckOffsetY()) _push = true;
		else _push = false;


		break;
	case PLAYSCENESTATE::BLOCK_MOVE_LEFT:

		for (int i = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(temp.y, _vBlock[i]->getOffsetX());
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}
		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i == j) continue;
				RECT temp;
				RECT iblock = _vBlock[i]->getRect();
				RECT jblock = _vBlock[j]->getRect();
				if (IntersectRect(&temp, &iblock, &jblock))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue() * 2;
						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}
		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_LEFT;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}


		break;
	case PLAYSCENESTATE::BLOCK_MOVE_RIGHT:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(temp.y, _vBlock[i]->getOffsetX());
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}

		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i == j) continue;
				RECT temp;
				RECT iblock = _vBlock[i]->getRect();
				RECT jblock = _vBlock[j]->getRect();
				if (IntersectRect(&temp, &iblock, &jblock))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue() * 2;
						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}

		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_RIGHT;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}

		break;
	case PLAYSCENESTATE::BLOCK_MOVE_UP:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(_vBlock[i]->getOffsetY(), temp.x);
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}

		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i == j) continue;
				RECT temp;
				RECT iblock = _vBlock[i]->getRect();
				RECT jblock = _vBlock[j]->getRect();
				if (IntersectRect(&temp, &iblock, &jblock))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue() * 2;
						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}

		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_UP;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}
		break;

	case PLAYSCENESTATE::BLOCK_MOVE_DOWN:
		for (int i = 0, count = 0; i < _vBlock.size(); i++)
		{
			POINT temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_EMPTY;
			_base[temp.y][temp.x].value = 0;
			_vBlock[i]->setLocation(_vBlock[i]->getOffsetY(), temp.x);
			temp = _vBlock[i]->getLocation();
			_base[temp.y][temp.x].state = BASE_FULL;
			_base[temp.y][temp.x].value = _vBlock[i]->getValue();
		}

		for (int i = 0; i < _vBlock.size(); i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (i == j) continue;
				RECT temp;
				RECT iblock = _vBlock[i]->getRect();
				RECT jblock = _vBlock[j]->getRect();
				if (IntersectRect(&temp, &iblock, &jblock))
				{
					if (_vBlock[i]->getIsCombine() == false)
					{
						_currentScore += _vBlock[i]->getValue() * 2;

						_vBlock[i]->Combine();
						_base[_vBlock[i]->getLocation().y][_vBlock[i]->getLocation().x].value = _vBlock[i]->getValue();
						_vBlock.erase(_vBlock.begin() + j);
						break;
					}
				}
			}
		}
		if (CheckState())
		{
			if (!_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_COMBINE_DOWN;
			}
			if (_isCombine)
			{
				_state = PLAYSCENESTATE::BLOCK_IDLE;
				_isCombine = false;
				pushBlock();
			}
		}
		break;

	case PLAYSCENESTATE::BLOCK_COMBINE_LEFT:

		_count = 0;

		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().x == i)
				{
					if (_base[_vBlock[j]->getLocation().y][i - 1].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetX(i - 1);
						_vBlock[j]->setIsCombine(true);
						_base[_vBlock[j]->getLocation().y][i].state = BASE_EMPTY;
						_base[_vBlock[j]->getLocation().y][i].value = 0;
						_count++;
					}
				}
			}
		}
		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_LEFT;
			_isCombine = true;
		}
		break;

	case PLAYSCENESTATE::BLOCK_COMBINE_RIGHT:
		_count = 0;
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().x == i)
				{
					if (_base[_vBlock[j]->getLocation().y][i + 1].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetX(i + 1);
						_vBlock[j]->setIsCombine(true);
						_base[_vBlock[j]->getLocation().y][i].state = BASE_EMPTY;
						_base[_vBlock[j]->getLocation().y][i].value = 0;
						_count++;
					}
				}
			}
		}
		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_RIGHT;
			_isCombine = true;
		}
		break;

	case PLAYSCENESTATE::BLOCK_COMBINE_UP:
		_count = 0;
		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().y == i)
				{
					if (_base[i - 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetY(i - 1);
						_vBlock[j]->setIsCombine(true);
						_base[i][_vBlock[j]->getLocation().x].state = BASE_EMPTY;
						_base[i][_vBlock[j]->getLocation().x].value = 0;
						_count++;
					}
				}
			}
		}
		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_UP;
			_isCombine = true;
		}
		break;

	case PLAYSCENESTATE::BLOCK_COMBINE_DOWN:
		_count = 0;
		for (int i = 2; i >= 0; i--)
		{
			for (int j = 0; j < _vBlock.size(); j++)
			{
				if (_vBlock[j]->getLocation().y == i)
				{
					if (_base[i + 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
					{
						_vBlock[j]->setOffsetY(i + 1);
						_vBlock[j]->setIsCombine(true);
						_base[i][_vBlock[j]->getLocation().x].state = BASE_EMPTY;
						_base[i][_vBlock[j]->getLocation().x].value = 0;
						_count++;
					}
				}
			}
		}
		if (_count == 0)
		{
			_state = PLAYSCENESTATE::BLOCK_IDLE;
			if (_push)
			{
				_push = false;
				this->pushBlock();
			}
		}
		else
		{
			_state = PLAYSCENESTATE::BLOCK_SET_DOWN;
			_isCombine = true;
		}
		break;

	case PLAYSCENESTATE::BLOCK_IDLE:
		if (INPUT->GetKeyDown(VK_LEFT))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_LEFT;
		}

		if (INPUT->GetKeyDown(VK_RIGHT))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_RIGHT;

		}
		if (INPUT->GetKeyDown(VK_UP))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_UP;

		}
		if (INPUT->GetKeyDown(VK_DOWN))
		{
			_state = PLAYSCENESTATE::BLOCK_SET_DOWN;

		}
		if (CheckBase() == false && CheckCombine() == false)
		{
			int data[18];
			data[0] = _hightScore;
			data[1] = _currentScore;
			int index = 2;
			for (int i = 0; i < 4; i++) 
			{
				for (int j = 0; j < 4; j++) 
				{
					data[index] = _base[i][j].value;
					index++;
				}
			}
			ScoreManager::getSingleton()->saveData("userdata.save", data);
		}
		break;
	}
}

void PlayScene::render()
{
	HDC hdc = getMemDC();
	IMAGEMANAGER->findImage("newGameButton")->render(hdc, _newGame.left, _newGame.top);
	HFONT fontRes =	CreateFont(33, 0, 0, 0, 700, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, "Arial");
	HFONT font2048 = CreateFont(90, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ANTIALIASED_QUALITY, 0, "Broadway");
	IMAGEMANAGER->findImage("base")->render(hdc, 100, 230);

	char temp[128];
	HFONT oFont = (HFONT)SelectObject(hdc, fontRes);
	SetTextColor(hdc, RGB(0, 128, 0));
	wsprintf(temp, "SCORE : %d", _currentScore);
	TextOut(hdc,315, 72, temp, strlen(temp));
	wsprintf(temp, "BEST : %d", _hightScore);
	TextOut(hdc, 325, 108, temp, strlen(temp));
	SelectObject(hdc, font2048);
	TextOut(hdc, 100, 60, "2048", 4);

	for (int i = 0; i < _vBlock.size(); i++)
	{
		_vBlock[i]->render();
	}

	if (CheckBase() == false && CheckCombine() == false)
	{
		SelectObject(hdc, font2048);
		IMAGEMANAGER->findImage("overlay")->alphaRender(hdc, 100, 230, 160);

		RECT cell = RectMake(100, 330, 370, 90);
		SetBkMode(hdc, 1);
		char temp[128];
		wsprintf(temp, "GAME OVER");
		SetTextColor(hdc, RGB(0, 0, 128));
		DrawText(hdc, temp, strlen(temp), &cell, DT_WORDBREAK | DT_CENTER | DT_NOCLIP | DT_EDITCONTROL);
	}

	oFont = (HFONT)SelectObject(getMemDC(), oFont);
	DeleteObject(oFont);
}

void PlayScene::pushBlock()
{
	int i = GetRandom(4);
	int j = GetRandom(4);
	while (_base[i][j].state == BASE_FULL)
	{
		i = GetRandom(4);
		j = GetRandom(4);
	}
	Block* bl = new Block;
	bl->init(i, j, 0);
	_vBlock.push_back(bl);
	_base[i][j].state = BASE_FULL;
	_base[i][j].value = bl->getValue();
}

bool PlayScene::CheckState()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if ((int)_vBlock[i]->getState() != 4)
		{
			return false;
		}
	}
	return true;
}

bool PlayScene::CheckOffsetX()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i]->getOffsetX() != _vBlock[i]->getLocation().x)
		{
			return true;
		}
	}
	return false;
}

bool PlayScene::CheckOffsetY()
{
	for (int i = 0; i < _vBlock.size(); i++)
	{
		if (_vBlock[i]->getOffsetY() != _vBlock[i]->getLocation().y)
		{
			return true;
		}
	}
	return false;
}

bool PlayScene::CheckCombine()
{
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().x == i)
			{
				if (_base[_vBlock[j]->getLocation().y][i - 1].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().x == i)
			{
				if (_base[_vBlock[j]->getLocation().y][i + 1].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	for (int i = 1; i < 4; i++)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().y == i)
			{
				if (_base[i - 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	for (int i = 2; i >= 0; i--)
	{
		for (int j = 0; j < _vBlock.size(); j++)
		{
			if (_vBlock[j]->getLocation().y == i)
			{
				if (_base[i + 1][_vBlock[j]->getLocation().x].value == _vBlock[j]->getValue())
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool PlayScene::CheckBase()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (_base[i][j].state == BASE_EMPTY) return true;
		}
	}
	return false;
}




