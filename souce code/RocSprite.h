#pragma once

#include <wincodec.h>
#include "RocController.h"

#pragma comment(lib, "windowscodecs")

class RocSprite
{
/// <summary>
/// ROC 中存储图片的对象，使用 windows code cs (WIC) 读取图片，转化成 direct 2d 的相应格式且存储。
/// </summary>
public:
	RocSprite(PCWSTR filename, INT width, INT height);
	~RocSprite();

	VOID Draw(FLOAT x, FLOAT y, FLOAT alpha);

private:
	ID2D1Bitmap* m_pBmp;
};