#include "RocSprite.h"

RocSprite::RocSprite(PCWSTR filename, INT width, INT height)
{
	m_pBmp = NULL;

	IWICImagingFactory* pWicFactory = NULL;
	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pFrame = NULL;
	IWICFormatConverter* pFormat = NULL;
	IWICBitmapScaler* pScaler = NULL;
	
	// ���� WIC Factory
	HRESULT hr = CoCreateInstance(
		CLSID_WICImagingFactory,          // ����� CLS ID   
		NULL,                             // Not part of an aggregate
		CLSCTX_INPROC_SERVER,             // dll ����ͬ�߳�����
		IID_IWICImagingFactory,           // ���������ͨ�ŵĽӿ�
		(LPVOID*)&pWicFactory             // WIC Factory ָ��
	);
	if (hr != S_OK) { MessageBox(NULL, L"���� WIC Factory ʧ��", L"", MB_OK); return; }


	// ���� Decoder
	hr = pWicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (hr != S_OK) { MessageBox(NULL, L"���� Decoder ʧ�ܣ���������ȱ��ͼƬ��Դ", L"", MB_OK); return; }

	// ��ȡһ֡
	hr = pDecoder->GetFrame(0, &pFrame);
	if (hr != S_OK) { MessageBox(NULL, L"GetFrame ʧ��", L"", MB_OK); return; }

	// ���� Format Converter
	hr = pWicFactory->CreateFormatConverter(&pFormat);
	if (hr != S_OK) { MessageBox(NULL, L"���� Converter ʧ��", L"", MB_OK); return; }

	// ���� Scalar
	hr = pWicFactory->CreateBitmapScaler(&pScaler);
	if (hr != S_OK) { MessageBox(NULL, L"���� Scalar ʧ��", L"", MB_OK); return; }

	// ��ʼ�� Scalar
	hr = pScaler->Initialize(
		pFrame,
		width,
		height,
		WICBitmapInterpolationModeCubic
	);
	if (hr != S_OK) { MessageBox(NULL, L"��ʼ�� Scalar ʧ��", L"", MB_OK); return; }

	// ��ʼ�� Format Converter
	hr = pFormat->Initialize(
		pScaler,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0f,
		WICBitmapPaletteTypeMedianCut
	);
	if (hr != S_OK) { MessageBox(NULL, L"��ʼ�� Converter ʧ��", L"", MB_OK); return; }

	// �� WIC bitmap ת��Ϊ ID2D Bitmap
	hr = RocController::GetStudio()->GetRenderTarget()->CreateBitmapFromWicBitmap(
		pFormat, &m_pBmp);
	if (hr != S_OK) { MessageBox(NULL, L"ת�� ID2DBitmap ʧ��", L"", MB_OK); return; }


	// �ͷ����� COM ���
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
		alpha, // ͸����
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, 
		D2D1::RectF(0.0f, 0.0f, m_pBmp->GetSize().width, m_pBmp->GetSize().height)    // src rect
	);
}
