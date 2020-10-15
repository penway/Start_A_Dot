#pragma once

#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1")
#pragma comment(lib, "dwrite")

class RocStudio
{
/// <summary>
/// ROC ����Ļ滭ģ�飬���� windows �� window handle
/// ������Դ������ RocStudio ����ͼ��Ļ��ƺ���Ⱦ
/// ʹ�� DirectX ģ���е� Direct 2D ����ͼ�κ�ͼƬ��Direct Write ���� TrueType����
/// </summary>
public:
	RocStudio();
	~RocStudio();

	BOOL Init(HWND hWnd);  // ��ʼ�� Studio���������еĻ�����Դ

	VOID BeginDraw();      // ��ʼ�滭
	VOID EndDraw();        // �����滭
	ID2D1HwndRenderTarget* GetRenderTarget();  // ��� RenderTarget

	// ������Ʒ���

	VOID ClearTheScreen(FLOAT r, FLOAT g, FLOAT b);  // ����
	VOID DrawText(WCHAR* string, UINT stringLength, D2D1_RECT_F* layoutRect);  // ��������
	VOID DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT stokeWidth);  // ������
	VOID DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT rgb, FLOAT a, FLOAT strokeWidth);                 
	VOID FillCircle(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT radius);                          // ����Բ
	VOID FillCircle(FLOAT rgb, FLOAT a, FLOAT x, FLOAT y, FLOAT radius);
	VOID FillSquare(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT width);                           // ���Ʒ���
	VOID FillRectangle(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT width, FLOAT height);          // ���ƾ���

private:
	// ���еĻ�����Դ
	ID2D1Factory* m_pFactory = NULL;           
	ID2D1HwndRenderTarget* m_pRenderTarget = NULL;
	ID2D1SolidColorBrush* m_pBrush = NULL;
	IDWriteFactory* m_pWriteFactory = NULL;
	IDWriteTextFormat* m_pTextFormat = NULL;
};
