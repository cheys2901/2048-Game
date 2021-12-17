#pragma once
#include "Scene.h"

enum class BLOCKMOVESTATE
{
	BLOCK_MOVE_LEFT,
	BLOCK_MOVE_RIGHT,
	BLOCK_MOVE_UP,
	BLOCK_MOVE_DOWN,
	BLOCK_IDLE
};

class Block : public Scene
{
private:
	BLOCKMOVESTATE _state;
	float _x, _y;
	RECT _rc;
	int _value;
	POINT _location;

	int _offsetX, _offsetY;
	bool _isCombine;

public:
	Block() {}
	~Block() {}

	HRESULT init(int i, int j, int value);
	void release();
	void update();
	void render();
	
	POINT getLocation() { return _location; }
	void setLocation(int i, int j);
	int getOffsetX() { return _offsetX; }
	int getOffsetY() { return _offsetY; }
	void setOffsetX(int x) { _offsetX = x; }
	void setOffsetY(int y) { _offsetY = y; }
	int getValue() { return _value; }
	void Combine() { _value *= 2; }
	RECT getRect() { return _rc; }
	BLOCKMOVESTATE getState() { return _state; }

	bool getIsCombine() { return _isCombine; }
	void setIsCombine(bool com) { _isCombine = com; }
};

