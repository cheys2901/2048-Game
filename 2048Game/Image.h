#pragma once
class Image
{
public:
	struct tagImageInfo
	{
		HDC hdc;
		HBITMAP hBit;
		HBITMAP hOBit;
		int width;
		int height;
		bool isTrans;
		COLORREF color;

		tagImageInfo()
		{
			hdc = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			width = 0;
			height = 0;
			isTrans = false;
			color = RGB(0, 0, 0);
		}
	};

private:
	tagImageInfo* _image;
	tagImageInfo* _blendImage;

	BLENDFUNCTION _blendFunction;

public:
	Image()
		:_image(nullptr) {}
	~Image() {}

	HRESULT init(int width, int height);
	HRESULT init(const char* fileName, int width, int height, bool trans, COLORREF color);
	HRESULT blendImageInit();

	void release();

	void render(HDC hdc, int destX, int destY);
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);
	void renderCenter(HDC hdc, int destX, int destY);
	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha);

	int getWidth() { return _image->width; }
	int getHeight() { return _image->height; }

	HDC getHDC() { return _image->hdc; }
};

