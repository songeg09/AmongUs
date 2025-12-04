#include "pch.h"
#include "UIElement.h"
#include "SceneManager.h"
#include "Texture.h"

UIElement::UIElement()
{
	m_pImage = nullptr;
	m_bVisibility = true;
}

UIElement::~UIElement()
{
}

void UIElement::Init(TEXTURE_TYPE _eTextureType, Vector2 _vec2RelativePosition, ANCHOR _eAnchor)
{
	m_pImage = ResourceManager::GetInstance()->LoadTexture(_eTextureType);
	m_eAnchor = _eAnchor;
	SetRelativePos(_vec2RelativePosition);
}

Vector2 UIElement::GetAbsoluteStartPos()
{
	Vector2 vec2AbsoluteStartPos = SceneManager::GetInstance()->GetCurScene()->GetViewportTopLeftInBackBuffer();
	vec2AbsoluteStartPos.m_fx += m_vec2RelativePosition.m_fx * ConstValue::vec2BaseWindowSize.m_fx;
	vec2AbsoluteStartPos.m_fy += m_vec2RelativePosition.m_fy * ConstValue::vec2BaseWindowSize.m_fy;

	switch (m_eAnchor)
	{
	case TOP_LEFT:
		break;
	case CENTER:
		vec2AbsoluteStartPos.m_fx -= m_pImage->GetWidth() / 2;
		vec2AbsoluteStartPos.m_fy -= m_pImage->GetHeight() / 2;
		break;
	case BOTTOM_RIGHT:
		vec2AbsoluteStartPos.m_fx -= m_pImage->GetWidth();
		vec2AbsoluteStartPos.m_fy -= m_pImage->GetHeight();
		break;
	}
	return vec2AbsoluteStartPos;
}
