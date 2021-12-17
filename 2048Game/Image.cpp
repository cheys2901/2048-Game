#include "stdafx.h"
#include "Image.h"

HRESULT Image::init(int width, int height)
{
	if (_image) release();

	HDC hdc = GetDC(_hWnd);

	_image = new tagImageInfo;
	_image->hdc = CreateCompatibleDC(hdc);
	_image->hBit = CreateCompatibleBitmap(hdc, width, height);
	_image->hOBit = (HBITMAP)SelectObject(_image->hdc, _image->hBit);
	_image->width = width;
	_image->height = height;

	if (!_image)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::init(const char * fileName, int width, int height, bool trans, COLORREF color)
{
	HDC hdc = GetDC(_hWnd);

	_image = new tagImageInfo;
	_image->hdc = CreateCompatibleDC(hdc);
	_image->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_image->hOBit = (HBITMAP)SelectObject(_image->hdc, _image->hBit);
	_image->width = width;
	_image->height = height;
	_image->isTrans = trans;
	_image->color = color;

	if (!_image)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT Image::blendImageInit()
{
	HDC hdc = GetDC(_hWnd);

	_blendImage = new tagImageInfo;
	_blendImage->hdc = CreateCompatibleDC(hdc);
	_blendImage->hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hdc, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	_blendFunction.AlphaFormat = 0;
	_blendFunction.BlendFlags = 0;
	_blendFunction.BlendOp = AC_SRC_OVER;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void Image::release()
{
	if (_image)
	{
		SelectObject(_image->hdc, _image->hOBit);
		DeleteObject(_image->hBit);
		DeleteDC(_image->hdc);
		SAFEDELETE(_image);
	}
}

void Image::render(HDC hdc, int destX, int destY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			SRCCOPY
		);
	}
}

void Image::renderCenter(HDC hdc, int deseX, int destY)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			deseX - _image->width/2,
			destY - _image->height/2,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			_image->width,
			_image->height,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			deseX - _image->width/2,
			destY - _image->height/2,
			_image->width,
			_image->height,
			_image->hdc,
			0, 0,
			SRCCOPY
		);
	}
}

void Image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_image->isTrans)
	{
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_image->hdc,
			sourX,
			sourY,
			sourWidth,
			sourHeight,
			_image->color
		);
	}
	else
	{
		BitBlt(
			hdc,
			destX,
			destY,
			sourWidth,
			sourHeight,
			_image->hdc,
			sourX,
			sourY,
			SRCCOPY
		);
	}
}

void Image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (offsetX < 0) offsetX = _image->width + (offsetX % _image->width);
	if (offsetY < 0) offsetY = _image->height + (offsetY % _image->height);

	RECT rcSour;
	int sourWidth;
	int sourHeight;

	RECT rcDest;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		rcSour.top = (y + offsetY) % _image->height;
		rcSour.bottom = _image->height;
		sourHeight = rcSour.bottom - rcSour.top;

		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			rcSour.left = (x + offsetX) % _image->width;
			rcSour.right = _image->width;
			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void Image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	if (!_blendImage) blendImageInit();

	_blendFunction.SourceConstantAlpha = alpha;

	if (_image->isTrans)
	{
		BitBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hdc, 0, 0,
			_image->width, _image->height, _image->hdc,
			0, 0, _image->width, _image->height, _image->color);

		GdiAlphaBlend(
			hdc, destX, destY,
			_image->width, _image->height, _blendImage->hdc, 0, 0, _image->width, _image->height, _blendFunction);

	}
	else
	{
		GdiAlphaBlend(hdc, destX, destY, _image->width, _image->height, _image->hdc, 0, 0, _image->width, _image->height, _blendFunction);
	}
}
