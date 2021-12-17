#pragma once
#include "SingletonBase.h"

class Scene;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, Scene*> mSceneList;
	typedef map<string, Scene*>::iterator miSceneList;

private:
	mSceneList _mSceneList;
	Scene* _currentScene;

public:
	SceneManager() : _currentScene(nullptr) {}
	~SceneManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	Scene* addScene(string sceneName, Scene* scene);
	HRESULT loadScene(string sceneName);

};

