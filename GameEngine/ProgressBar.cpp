#include "pch.h"
#include "ProgressBar.h"
#include "ResourceManager.h"
#include "Texture.h"

ProgressBar::ProgressBar()
{
	m_pProgressBar = nullptr;
	m_fProgress = 0.0f;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Init(TEXTURE_TYPE _eFrame, TEXTURE_TYPE _eProgress, Vector2 _vec2RelativePosition, ANCHOR _eAnchor)
{
	UIElement::Init(_eFrame, _vec2RelativePosition, _eAnchor);
	m_pProgressBar = ResourceManager::GetInstance()->LoadTexture(_eProgress);

	m_vec2ProgressStartPos = m_vecAbsoluteStartPos;
	m_vec2ProgressStartPos.m_fx += m_pImage->GetWidth() / 2;
	m_vec2ProgressStartPos.m_fy += m_pImage->GetHeight() / 2;

	m_vec2ProgressStartPos.m_fx -= m_pProgressBar->GetWidth() / 2;
	m_vec2ProgressStartPos.m_fy -= m_pProgressBar->GetHeight() / 2;
}

void ProgressBar::Update()
{
}

void ProgressBar::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	// 프레임 그리기
	TransparentBlt(_memDC, 
		m_vecAbsoluteStartPos.m_fx, m_vecAbsoluteStartPos.m_fy,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		m_pImage->GetDC(),
		0, 0,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		RGB(255, 0, 255)
	);

	// 진행상황 그리기
	TransparentBlt(_memDC,
		m_vec2ProgressStartPos.m_fx, m_vec2ProgressStartPos.m_fy,
		m_pProgressBar->GetWidth() * m_fProgress, m_pProgressBar->GetHeight(),
		m_pProgressBar->GetDC(),
		0, 0,
		m_pProgressBar->GetWidth() * m_fProgress, m_pProgressBar->GetHeight(),
		RGB(255, 0, 255)
	);
}
