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
	m_bHover = false;
	m_pImage = nullptr;
}

Button::~Button()
{
}


void Button::Init(TEXTURE_TYPE _eTextureType, Vector2 _vec2RelativePosition, std::function<void()> _callBackFunc)
{
	UIElement::Init(_vec2RelativePosition);
	m_callBackFunc = _callBackFunc;
	m_pImage = ResourceManager::GetInstance()->LoadTexture(_eTextureType);
}

void Button::Update()
{
	POINT m_ptMouse;
	GetCursorPos(&m_ptMouse);
	ScreenToClient(Core::GetInstance()->GethWnd(), &m_ptMouse);

	Vector2 vec2AbsolutePosision = SceneManager::GetInstance()->GetCurScene()->GetViewportTopLeftInBackBuffer();
	vec2AbsolutePosision += ConstValue::vec2BaseWindowSize;
	vec2AbsolutePosision = m_vec2RelativePosition * vec2AbsolutePosision;

	RECT btnArea = {
		vec2AbsolutePosision.m_fx - m_pImage->GetWidth() / 2,
		vec2AbsolutePosision.m_fy - m_pImage->GetHeight() / 2,
		vec2AbsolutePosision.m_fx + m_pImage->GetWidth() / 2,
		vec2AbsolutePosision.m_fy + m_pImage->GetHeight() / 2
	};

	if (PtInRect(&btnArea, m_ptMouse))
	{
		m_bHover = true;
		if (InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_STATE::DOWN)
			m_callBackFunc();
	}
	else
		m_bHover = false;
		
}

Vector2 Button::GetAbsoluteStartPosition()
{
	Vector2 vec2AbsoluteStartPosition = SceneManager::GetInstance()->GetCurScene()->GetViewportTopLeftInBackBuffer();
	vec2AbsoluteStartPosition.m_fx += (ConstValue::vec2BaseWindowSize.m_fx * m_vec2RelativePosition.m_fx);
	vec2AbsoluteStartPosition.m_fy += (ConstValue::vec2BaseWindowSize.m_fy * m_vec2RelativePosition.m_fy);

	vec2AbsoluteStartPosition.m_fx -= m_pImage->GetWidth() / 2;
	vec2AbsoluteStartPosition.m_fy -= m_pImage->GetHeight() / 2;

	return vec2AbsoluteStartPosition;
}

void Button::Render(HDC _memDC)
{
	Vector2 vec2StartPos = GetAbsoluteStartPosition();

	TransparentBlt(
		_memDC, vec2StartPos.m_fx, vec2StartPos.m_fy,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		m_pImage->GetDC(),
		0,0,
		m_pImage->GetWidth(), m_pImage->GetHeight(),
		RGB(255,0,255)
	);

	if (m_bHover)
	{
		AlphaBlend(
			_memDC, vec2StartPos.m_fx, vec2StartPos.m_fy,
			m_pImage->GetWidth(), m_pImage->GetHeight(),
			m_pImage->GetDC(),
			0, 0,
			m_pImage->GetWidth(), m_pImage->GetHeight(),
			GDIManager::GetInstance()->GetBlendFunction()
		);
	}
}
