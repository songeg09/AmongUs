#include "pch.h"
#include "Button.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "Core.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Init(Vector2 _vec2RelativePosition, Vector2 _vec2Size, std::function<void()> _callBackFunc)
{
	UIElement::Init(_vec2RelativePosition);
	m_vec2Size = _vec2Size;
	m_callBackFunc = _callBackFunc;
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
		vec2AbsolutePosision.m_fx - m_vec2Size.m_fx / 2,
		vec2AbsolutePosision.m_fy - m_vec2Size.m_fy / 2,
		vec2AbsolutePosision.m_fx + m_vec2Size.m_fx / 2,
		vec2AbsolutePosision.m_fy + m_vec2Size.m_fy / 2
	};

	if (PtInRect(&btnArea, m_ptMouse) && InputManager::GetInstance()->GetKeyState(VK_LBUTTON) == KEY_STATE::DOWN)
		m_callBackFunc();
}

void Button::Render(HDC _memDC)
{
	Vector2 vec2AbsolutePosision = SceneManager::GetInstance()->GetCurScene()->GetViewportTopLeftInBackBuffer();
	vec2AbsolutePosision += ConstValue::vec2BaseWindowSize;
	vec2AbsolutePosision = m_vec2RelativePosition * vec2AbsolutePosision;

	Rectangle(_memDC,
		vec2AbsolutePosision.m_fx - m_vec2Size.m_fx / 2,
		vec2AbsolutePosision.m_fy - m_vec2Size.m_fy / 2, 
		vec2AbsolutePosision.m_fx + m_vec2Size.m_fx / 2,
		vec2AbsolutePosision.m_fy + m_vec2Size.m_fy / 2
	);
}
