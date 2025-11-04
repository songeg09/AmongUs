#include "pch.h"
#include "Texture.h"
#include "Core.h"

Texture::Texture()
{
	m_BitMapInfomation = {};
	m_hBitMap = nullptr;
	m_hDC = nullptr;
}

Texture::~Texture()
{
}

void Texture::Load(std::wstring _strFilePath)
{
	m_hBitMap = (HBITMAP)LoadImageW(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBitMap != nullptr);

	m_hDC = CreateCompatibleDC(Core::GetInstance()->GetMainDC());

	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hDC, m_hBitMap);
	DeleteObject(hPrevBitMap);

	GetObject(m_hBitMap, sizeof(BITMAP), &m_BitMapInfomation);
}

void Texture::LoadPartially(std::wstring _strFilePath, int i, int j, int size)
{
    HBITMAP hSrc = (HBITMAP)LoadImageW(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0,
        LR_CREATEDIBSECTION | LR_LOADFROMFILE);
    assert(hSrc != nullptr);
	
	HDC srcDC  = CreateCompatibleDC(Core::GetInstance()->GetMainDC());
	
	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(srcDC, hSrc);
	DeleteObject(hPrevBitMap);

    m_hDC = CreateCompatibleDC(Core::GetInstance()->GetMainDC());
	BITMAPINFO bi{};
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = size;
	bi.bmiHeader.biHeight = -size;   // top-down
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	void* pBits = nullptr;
	HBITMAP m_hBitMap = CreateDIBSection(Core::GetInstance()->GetMainDC(), &bi, DIB_RGB_COLORS, &pBits, nullptr, 0);
	hPrevBitMap = (HBITMAP)SelectObject(m_hDC, m_hBitMap);
	DeleteObject(hPrevBitMap);

	const int srcX = j * size;
	const int srcY = i * size;
	bool ok = BitBlt(m_hDC, 0, 0, size, size, srcDC, srcX, srcY, SRCCOPY);
	
	GetObject(m_hBitMap, sizeof(BITMAP), &m_BitMapInfomation);
}

