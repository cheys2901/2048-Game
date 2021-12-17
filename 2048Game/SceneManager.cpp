#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"

HRESULT SceneManager::init()
{
	return S_OK;
}

void SceneManager::release()
{
	for (auto scene : _mSceneList)
	{
		scene.second->release();
		SAFEDELETE(scene.second);
	}
}

void SceneManager::update()
{
	if (_currentScene)
	{
		_currentScene->update();
	}
}

void SceneManager::render()
{
	if (_currentScene)
	{
		_currentScene->render();
	}
}

Scene * SceneManager::addScene(string sceneName, Scene * scene)
{
	if (!scene) return nullptr;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);
	if (find == _mSceneList.end())
	{
		return E_FAIL;
	}

	if (find->second == _currentScene)
	{
		return E_FAIL;
	}

	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_NOTIMPL;
}
