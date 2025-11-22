#include "pch.h"
#include "TimingBar.h"
#include "ResourceManager.h"
#include "TimerManager.h"
#include "Texture.h"

TimingBar::TimingBar()
{
	m_pTimingCursor = nullptr;
	m_bPlaying = false;
	m_fCycleTime = 0.0f;
	m_fRatio = 0.0f;
}

TimingBar::~TimingBar()
{
}

void TimingBar::Init(TEXTURE_TYPE _pTimingBar, TEXTURE_TYPE _pTimingCursor, Vector2 _vec2RelativePosition, ANCHOR _eAnchor, std::function<void()> _funcOnSuccessCallback, std::function<void()> _funcOnFailCallback)
{
	UIElement::Init(_pTimingBar, _vec2RelativePosition, _eAnchor);
	m_pTimingCursor = ResourceManager::GetInstance()->LoadTexture(_pTimingCursor);

	m_funcOnSuccessCallback = _funcOnSuccessCallback;
	m_funcOnFailCallback = _funcOnFailCallback;

	m_vec2InitialCursorPos = m_vecAbsoluteStartPos;
	m_vec2InitialCursorPos.m_fy = m_vecAbsoluteStartPos.m_fy + m_pImage->GetHeight() / 2;
	m_vec2InitialCursorPos.m_fy -= m_pTimingCursor->GetHeight()/2;
	m_vec2InitialCursorPos.m_fx -= m_pTimingCursor->GetWidth()/2;
}

void TimingBar::Update()
{
	if (m_bVisibility == false || m_bPlaying == false)
		return;

	m_fElapsedTime += TimerManager::GetInstance()->GetfDeltaTime();
	m_fElapsedTime = std::fmod(m_fElapsedTime, m_fCycleTime);
	
	m_fRatio = (m_fElapsedTime * 2) / m_fCycleTime;
	if (m_fRatio > 1.0f)
		m_fRatio = 2.0f - m_fRatio;
	m_vec2CursorPos.m_fx = m_vec2InitialCursorPos.m_fx + m_pImage->GetWidth() * m_fRatio;
}

void TimingBar::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	TransparentBlt(_memDC,
		m_vecAbsoluteStartPos.m_fx, m_vecAbsoluteStartPos.m_fy,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		m_pImage->GetDC(),
		0, 0,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		RGB(255, 0, 255)
	);

	TransparentBlt(_memDC,
		m_vec2CursorPos.m_fx, m_vec2CursorPos.m_fy,
		m_pTimingCursor->GetWidth(), m_pTimingCursor->GetHeight(),
		m_pTimingCursor->GetDC(),
		0, 0,
		m_pTimingCursor->GetWidth(), m_pTimingCursor->GetHeight(),
		RGB(255, 0, 255)
	);
}

void TimingBar::Reset()
{
	m_fElapsedTime = 0;
	m_fRatio = 0;
	m_vec2CursorPos = m_vec2InitialCursorPos;
}

void TimingBar::Start()
{
	m_bPlaying = true;
}

void TimingBar::Stop()
{
	m_bPlaying = false;

	if (abs((m_fCycleTime / 2) - m_fElapsedTime) < m_fCycleTime * 0.1f)	// 오차 10퍼센트
	{
		if(m_funcOnSuccessCallback != nullptr)
			m_funcOnSuccessCallback();
	}
	else
	{
		if (m_funcOnFailCallback != nullptr)
			m_funcOnFailCallback();
	}
}

