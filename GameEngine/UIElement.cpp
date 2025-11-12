#include "pch.h"
#include "UIElement.h"

UIElement::UIElement()
{
}

UIElement::~UIElement()
{
}

void UIElement::Init(Vector2 _vec2RelativePosition)
{
	m_vec2RelativePosition = _vec2RelativePosition;
}
