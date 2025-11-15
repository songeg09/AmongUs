#pragma once
#include "UIElement.h"


class Texture;
class Button : public UIElement
{
private:
	
	std::function<void()>	m_callBackFunc;
	bool					m_bActivate;

	RECT					m_btnArea;
	

public:
	Button();
	~Button();

	void Init(TEXTURE_TYPE _eTextureType, Vector2 _vec2RelativePosition, UIElement::ANCHOR _eAnchor, std::function<void()> _callBackFunc = nullptr, bool _bActivate = true);
	void Update() override;
	void Render(HDC _memDC) override;
	void SetActivate(bool _bActiavet) { m_bActivate = _bActiavet; }

};

