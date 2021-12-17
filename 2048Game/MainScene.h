#pragma once
#include "Scene.h"

class MainScene : public Scene
{
private:
	int _offsetX;
	int _offsetY;

	RECT _start;
	RECT _exit;

public:
	MainScene() {}
	~MainScene() {}

	HRESULT init();
	void release();
	void update();
	void render();

};

