#include "RocSprite.h"

RocSprite::RocSprite(PCWSTR filename, INT width, INT height)
{
	m_pBmp = NULL;

	IWICImagingFactory* pWicFactory = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pFormat = NULL;
	IWICBitmapScaler* pScaler = NULL;
	
	// 创建 WIC Factory
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,          // 对象的 CLS ID   
		NULL,                             // Not part of an aggregate
		CLSCTX_INPROC_SERVER,             // dll 在相同线程运行
		IID_IWICImagingFactory,           // 引用与对象通信的接口
		(LPVOID*)&pWicFactory             // WIC Factory 指针
	);
	if (hr != S_OK) { MessageBox(NULL, L"创建 WIC Factory 失败", L"", MB_OK); return; }


	// 创建 Decoder
	hr = pWicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (hr != S_OK) { MessageBox(NULL, L"创建 Decoder 失败，可能由于缺少图片资源", L"", MB_OK); return; }

	// 读取一帧
	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK) { MessageBox(NULL, L"GetFrame 失败", L"", MB_OK); return; }

	// 创建 Format Converter
	hr = pWicFactory->CreateFormatConverter(&pFormat);
	if (hr != S_OK) { MessageBox(NULL, L"创建 Converter 失败", L"", MB_OK); return; }

	// 创建 Scalar
	hr = pWicFactory->CreateBitmapScaler(&pScaler);
	if (hr != S_OK) { MessageBox(NULL, L"创建 Scalar 失败", L"", MB_OK); return; }

	// 初始化 Scalar
	hr = pScaler->Initialize(
		pFrame,
		width,
		height,
		WICBitmapInterpolationModeCubic
	);
	if (hr != S_OK) { MessageBox(NULL, L"初始化 Scalar 失败", L"", MB_OK); return; }

	// 初始化 Format Converter
	hr = pFormat->Initialize(
		pScaler,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0f,
		WICBitmapPaletteTypeMedianCut
	);
	if (hr != S_OK) { MessageBox(NULL, L"初始化 Converter 失败", L"", MB_OK); return; }

	// 将 WIC bitmap 转换为 ID2D Bitmap
	hr = RocController::GetStudio()->GetRenderTarget()->CreateBitmapFromWicBitmap(
		pFormat, &m_pBmp);
	if (hr != S_OK) { MessageBox(NULL, L"转换 ID2DBitmap 失败", L"", MB_OK); return; }


	// 释放所有 COM 组件
	if (pWicFactory) pWicFactory->Release();
	if (pFrame)      pFrame->Release();
	if (pDecoder)    pDecoder->Release();
	if (pScaler)     pScaler->Release();
	if (pFormat)     pFormat->Release();
}

RocSprite::~RocSprite()
{
	if (m_pBmp) m_pBmp->Release();
}

VOID RocSprite::Draw(FLOAT x, FLOAT y, FLOAT alpha)
{
	RocController::GetStudio()->GetRenderTarget()->DrawBitmap(
		m_pBmp,
		D2D1::RectF(x, y, x + m_pBmp->GetSize().width, y + m_pBmp->GetSize().height),   // dst rect
		alpha, // 透明度
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
		D2D1::RectF(0.0f, 0.0f, m_pBmp->GetSize().width, m_pBmp->GetSize().height)    // src rect
	);
}
