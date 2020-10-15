#pragma once

#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

class RocStudio
{
/// <summary>
/// ROC 引擎的绘画模块，连接 windows 的 window handle
/// 所有资源都调用 RocStudio 进行图像的绘制和渲染
/// 使用 DirectX 模块中的 Direct 2D 绘制图形和图片，Direct Write 绘制 TrueType文字
/// </summary>
public:
	RocStudio();
	~RocStudio();

	BOOL Init(HWND hWnd);  // 初始化 Studio，申请所有的绘制资源

	VOID BeginDraw();      // 开始绘画
	VOID EndDraw();        // 结束绘画
	ID2D1HwndRenderTarget* GetRenderTarget();  // 获得 RenderTarget

	// 具体绘制方法

	VOID ClearTheScreen(FLOAT r, FLOAT g, FLOAT b);  // 清屏
	VOID DrawText(WCHAR* string, UINT stringLength, D2D1_RECT_F* layoutRect);  // 绘制文字
	VOID DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT stokeWidth);  // 绘制线
	VOID DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT rgb, FLOAT a, FLOAT strokeWidth);                 
	VOID FillCircle(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT radius);                          // 绘制圆
	VOID FillCircle(FLOAT rgb, FLOAT a, FLOAT x, FLOAT y, FLOAT radius);
	VOID FillSquare(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT width);                           // 绘制方形
	VOID FillRectangle(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT width, FLOAT height);          // 绘制矩形

private:
	// 所有的绘制资源
	ID2D1Factory* m_pFactory = NULL;           
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
	ID2D1SolidColorBrush* m_pBrush = NULL;
	IDWriteFactory* m_pWriteFactory = NULL;
	IDWriteTextFormat* m_pTextFormat = NULL;
};
