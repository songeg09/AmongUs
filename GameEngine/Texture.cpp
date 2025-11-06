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

void Texture::LoadFlipped(Texture* _srcTexture)
{
	m_hDC = CreateCompatibleDC(Core::GetInstance()->GetMainDC());

	m_hBitMap = CreateCompatibleBitmap(Core::GetInstance()->GetMainDC(), _srcTexture->GetWidth(), _srcTexture->GetHeight());

	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hDC, m_hBitMap);
	DeleteObject(hPrevBitMap);

	StretchBlt(
		m_hDC, 0, 0, _srcTexture->GetWidth(), _srcTexture->GetHeight(),    // 목적지
		_srcTexture->GetDC(), _srcTexture->GetWidth() - 1, 0, -_srcTexture->GetWidth(), _srcTexture->GetHeight(),    // 소스: xSrc=w-1, cxSrc=-w → 좌우반전
		SRCCOPY
	);

	GetObject(m_hBitMap, sizeof(BITMAP), &m_BitMapInfomation);
}

