#pragma once
#include "Button.h"

class NumPadButton: public Button
{
private:
	bool m_bSelected;

public:
	NumPadButton();
	~NumPadButton();

	void Init(TEXTURE_TYPE _eTextureType, Vector2 _absolutePosition, UIElement::ANCHOR _eAnchor, std::function<void()> _callBackFunc = nullptr, bool _bActivate = true);
	void SetBtnArea() override;
	
	Vector2 GetAbsoluteStartPos() { return m_vecAbsoluteStartPos; }
	void SetAbsoluteStartpos(Vector2 _vec2AbsoluteStartPos) { m_vecAbsoluteStartPos = _vec2AbsoluteStartPos; }
};

