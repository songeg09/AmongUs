#include "pch.h"
#include "Button.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Core.h"
#include "Texture.h"
#include "GDIManager.h"

Button::Button()
{
	m_callBackFunc = nullptr;
	m_bActivate = true;
	m_pImage = nullptr;
}

Button::~Button()
{
}


void Button::Init(TEXTURE_TYPE _eTextureType, Vector2 _vec2RelativePosition, UIElement::ANCHOR _eAnchor, std::function<void()> _callBackFunc, bool _bActivate)
{
	UIElement::Init(_eTextureType, _vec2RelativePosition, _eAnchor);
	m_callBackFunc = _callBackFunc;
	SetActivate(_bActivate);

	Vector2 btnAreaStartPos = m_vec2RelativePosition * ConstValue::vec2BaseWindowSize;
	btnAreaStartPos.m_fx -= m_pImage->GetWidth() / 2;
	btnAreaStartPos.m_fy -= m_pImage->GetHeight() / 2;

	m_btnArea = {
		(long)btnAreaStartPos.m_fx,
		(long)btnAreaStartPos.m_fy,
		(long)btnAreaStartPos.m_fx + m_pImage->GetWidth(),
		(long)btnAreaStartPos.m_fy + m_pImage->GetHeight()
	};

}

void Button::Update()
{
	if (m_bActivate == false || m_bVisibility == false)
		return;

	POINT m_ptMouse;
	GetCursorPos(&m_ptMouse);
	ScreenToClient(Core::GetInstance()->GethWnd(), &m_ptMouse);

	if (PtInRect(&m_btnArea, m_ptMouse) && InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_STATE::DOWN)
		m_callBackFunc();
		
}

void Button::Render(HDC _memDC)
{
	if (m_bVisibility == false)
		return;

	HDC hAlphaDC = GDIManager::GetInstance()->GetBtnConfigureDC();

	BitBlt(
		hAlphaDC,
		0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(),
		_memDC,
		m_vecAbsoluteStartPos.m_fx,
		m_vecAbsoluteStartPos.m_fy,
		SRCCOPY
	);

	TransparentBlt(
		hAlphaDC,
		0, 0,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		m_pImage->GetDC(),
		0, 0,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		RGB(255, 0, 255)
	);

	// 활성화 되어 있지 않은 경우 투명 효과 적용
	if (m_bActivate == false)
	{
		AlphaBlend(
			_memDC, 
			m_vecAbsoluteStartPos.m_fx, m_vecAbsoluteStartPos.m_fy,
			m_pImage->GetWidth(), m_pImage->GetHeight(),
			hAlphaDC,
			0, 0,
			m_pImage->GetWidth(), m_pImage->GetHeight(),
			GDIManager::GetInstance()->GetBlendFunction()
		);
	}
	else
	{
		BitBlt(_memDC, 
			m_vecAbsoluteStartPos.m_fx, m_vecAbsoluteStartPos.m_fy,
			m_pImage->GetWidth(), m_pImage->GetHeight(),
			hAlphaDC,
			0, 0,
			SRCCOPY
		);
	}
}
