#include "stdafx.h"
#include "ImageManager.h"

Image * ImageManager::addImage(string key, int width, int height)
{
	Image* img = findImage(key);

	if (img) return img;

	img = new Image;
	if (FAILED(img->init(width, height)))
	{
		img->release();
		SAFEDELETE(img);
		return nullptr;
	}
	_mImage.insert(make_pair(key, img));
	return img;
}

Image * ImageManager::addImage(string key, const char * fileName, int width, int height, bool trans, COLORREF color)
{
	Image* img = findImage(key);

	if (img) return img;

	img = new Image;
	if (FAILED(img->init(fileName, width, height, trans, color)))
	{
		img->release();
		SAFEDELETE(img);
		return nullptr;
	}

	_mImage.insert(make_pair(key, img));

	return img;
}

Image * ImageManager::findImage(string key)
{
	mImageIter _key = _mImage.find(key);

	if (_key != _mImage.end())
	{
		return _key->second;
	}

	return nullptr;
}

bool ImageManager::deleteImage(string key)
{
	mImageIter _key = _mImage.find(key);

	if (_key != _mImage.end())
	{
		_key->second->release();
		SAFEDELETE(_key->second);
		_mImage.erase(_key);

		return true;
	}

	return false;
}

void ImageManager::clearImage()
{
	_mImage.clear();
}
