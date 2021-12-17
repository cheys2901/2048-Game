#pragma once
#include "SingletonBase.h"
#include "Image.h"
class ImageManager : public SingletonBase<ImageManager>
{
private:
	map<string, Image*> _mImage;
	typedef map<string, Image*>::iterator mImageIter;

public:
	ImageManager() {}
	~ImageManager() {}

	Image* addImage(string key, int width, int height);
	Image* addImage(string key, const char* fileName, int width, int height, bool trans, COLORREF color);
	Image* findImage(string key);
	bool deleteImage(string key);
	void clearImage();
};

