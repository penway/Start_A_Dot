#pragma once

#include <wincodec.h>
#include "RocController.h"

#pragma comment(lib, "windowscodecs")

class RocSprite
{
/// <summary>
/// ROC �д洢ͼƬ�Ķ���ʹ�� windows code cs (WIC) ��ȡͼƬ��ת���� direct 2d ����Ӧ��ʽ�Ҵ洢��
/// </summary>
public:
	RocSprite(PCWSTR filename, INT width, INT height);
	~RocSprite();

	VOID Draw(FLOAT x, FLOAT y, FLOAT alpha);

private:
	ID2D1Bitmap* m_pBmp;
};