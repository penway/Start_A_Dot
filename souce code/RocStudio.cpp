#include "RocStudio.h"

RocStudio::RocStudio()
{

}


RocStudio::~RocStudio()
{
	// 释放所有 COM 变量
	if (m_pFactory)
		m_pFactory->Release();
	if (m_pRenderTarget)
		m_pRenderTarget->Release();
	if (m_pBrush)
		m_pBrush->Release();
}


BOOL RocStudio::Init(HWND hWnd)
{
	HRESULT result;  // 检测创建成功与否

	// 初始化 D2D1 Factory
	result = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_MULTI_THREADED,     // 多线程工厂
		&m_pFactory
	);
	if (result != S_OK) { MessageBox(hWnd, L"初始化 D2D1 Factory 失败", L"", MB_OK); return FALSE; }

	// 初始化 RenderTarget
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	result = m_pFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(clientRect.right, clientRect.bottom)),
		&m_pRenderTarget
	);
	if (result != S_OK) { MessageBox(hWnd, L"初始化 Render Target 失败", L"", MB_OK);  return FALSE; }

	// 初始化 Brush
	result = m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &m_pBrush);
	if (result != S_OK) { MessageBox(hWnd, L"初始化 Brush 失败", L"", MB_OK);  return FALSE; }

	// 初始化 Direct Write Factory
	result = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory)
	);
	if (result != S_OK) { MessageBox(hWnd, L"初始化 Direct Write Factory 失败", L"", MB_OK);  return FALSE; }

	// 初始化 Direct Write Text Format
	result = m_pWriteFactory->CreateTextFormat(
		L"Verdana", 
		NULL,                          // Font collection(NULL sets it to the system font collection)
		DWRITE_FONT_WEIGHT_REGULAR,    // Weight
		DWRITE_FONT_STYLE_NORMAL,      // Style
		DWRITE_FONT_STRETCH_NORMAL,    // Stretch
		24.0f,                         // Size    
		L"en-us",                      // Local
		&m_pTextFormat                 // Pointer to recieve the created object
	);
	if (result != S_OK) { MessageBox(hWnd, L"初始化 Direct Write Text Format 失败", L"", MB_OK);  return FALSE; }

	return TRUE;
}


VOID RocStudio::BeginDraw()
{
	m_pRenderTarget->BeginDraw();
}


VOID RocStudio::EndDraw()
{
	m_pRenderTarget->EndDraw();
}

ID2D1HwndRenderTarget* RocStudio::GetRenderTarget()
{
	return m_pRenderTarget;
}


VOID RocStudio::ClearTheScreen(FLOAT r, FLOAT g, FLOAT b)
{
	m_pRenderTarget->Clear(D2D1::ColorF(r, g, b));
}

VOID RocStudio::DrawText(WCHAR* string, UINT stringLength, D2D1_RECT_F* layoutRect)
{
	m_pBrush->SetColor(D2D1::ColorF(0.0f, 0.0f, 0.0f));
	m_pRenderTarget->DrawTextW(
		string,
		stringLength,
		m_pTextFormat, 
		layoutRect, 
		m_pBrush
	);
}

VOID RocStudio::DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT strokeWidth)
{
	m_pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), m_pBrush, strokeWidth);
}

VOID RocStudio::DrawLine(FLOAT x1, FLOAT y1, FLOAT x2, FLOAT y2, FLOAT rgb, FLOAT a, FLOAT strokeWidth)
{
	m_pBrush->SetColor(D2D1::ColorF(rgb, a));
	m_pRenderTarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), m_pBrush, strokeWidth);
}

VOID RocStudio::FillCircle(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT radius)
{
	m_pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	m_pRenderTarget->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius),
		m_pBrush);
}

VOID RocStudio::FillCircle(FLOAT rgb, FLOAT a, FLOAT x, FLOAT y, FLOAT radius)
{
	m_pBrush->SetColor(D2D1::ColorF(rgb, a));
	m_pRenderTarget->FillEllipse(
		D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius),
		m_pBrush);
}

VOID RocStudio::FillSquare(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT width)
{
	m_pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::Rect(x - width / 2, y - width / 2, x + width / 2, y + width / 2);
	m_pRenderTarget->FillRectangle(&rect, m_pBrush);
}

VOID RocStudio::FillRectangle(FLOAT r, FLOAT g, FLOAT b, FLOAT a, FLOAT x, FLOAT y, FLOAT width, FLOAT height)
{
	m_pBrush->SetColor(D2D1::ColorF(r, g, b, a));
	D2D1_RECT_F rect = D2D1::Rect(x, y, x + width, y + height);
	m_pRenderTarget->FillRectangle(&rect, m_pBrush);
}
