#include "pch.h"
#include "NumPadButton.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Texture.h"

NumPadButton::NumPadButton()
{
	m_bSelected = false;
}

NumPadButton::~NumPadButton()
{

}

void NumPadButton::Init(TEXTURE_TYPE _eTextureType, Vector2 _absolutePosition, UIElement::ANCHOR _eAnchor, std::function<void()> _callBackFunc, bool _bActivate)
{
	m_pImage = ResourceManager::GetInstance()->LoadTexture(_eTextureType);
	m_vecAbsoluteStartPos = _absolutePosition;
	m_eAnchor = _eAnchor;
	m_callBackFunc = _callBackFunc;
	m_bActivate = _bActivate;

	SetBtnArea();
}

void NumPadButton::SetBtnArea()
{
	Vector2 vecRelativeStartPosInViewPort = m_vecAbsoluteStartPos;
	vecRelativeStartPosInViewPort.m_fx -= ConstValue::fGameSceneGaurdBandPx;
	vecRelativeStartPosInViewPort.m_fy -= ConstValue::fGameSceneGaurdBandPx;

	switch (m_eAnchor)
	{
	case ANCHOR::TOP_LEFT:
		break;
	case ANCHOR::CENTER:
		vecRelativeStartPosInViewPort.m_fx -= m_pImage->GetWidth() / 2;
		vecRelativeStartPosInViewPort.m_fy -= m_pImage->GetHeight() / 2;
		break;
	case ANCHOR::BOTTOM_RIGHT:
		vecRelativeStartPosInViewPort.m_fx -= m_pImage->GetWidth();
		vecRelativeStartPosInViewPort.m_fy -= m_pImage->GetHeight();
		break;
	}

	m_btnArea = {
		(long)vecRelativeStartPosInViewPort.m_fx,
		(long)vecRelativeStartPosInViewPort.m_fy,
		(long)vecRelativeStartPosInViewPort.m_fx + m_pImage->GetWidth(),
		(long)vecRelativeStartPosInViewPort.m_fy + m_pImage->GetHeight()
	};
}


