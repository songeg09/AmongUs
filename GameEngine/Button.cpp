#include "pch.h"
#include "Button.h"
#include "SceneManager.h"
#include "InputManager.h"

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
	
}

void Button::Render(HDC _memDC)
{
	Vector2 vec2AbsolutePosision = SceneManager::GetInstance()->GetCurScene()->GetViewportTopLeftInBackBuffer();
	vec2AbsolutePosision += SceneManager::GetInstance()->GetCurScene()->GetViewPortSize();
	vec2AbsolutePosision = m_vec2RelativePosition * vec2AbsolutePosision;

	Rectangle(_memDC,
		vec2AbsolutePosision.m_fx - m_vec2Size.m_fx / 2,
		vec2AbsolutePosision.m_fy - m_vec2Size.m_fy / 2, 
		vec2AbsolutePosision.m_fx + m_vec2Size.m_fx / 2,
		vec2AbsolutePosision.m_fy + m_vec2Size.m_fy / 2
	);
}
