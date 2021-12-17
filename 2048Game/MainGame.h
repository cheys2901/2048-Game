#pragma once
#include "Scene.h"
#include "MainScene.h"
#include "PlayScene.h"

struct tagTailInfo
{
	bool isEmpty;
	int space;
};

class mainGame : public Scene
{
private:


public:
	mainGame() {}
	~mainGame() {}

	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
	void imageInit();
	
};

