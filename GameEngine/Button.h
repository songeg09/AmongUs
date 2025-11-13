#pragma once
#include "UIElement.h"
#include "ResourceManager.h"

class Texture;
class Button : public UIElement
{
private:
	//Vector2		m_vec2Size;
	Texture*	m_pImage;
	std::function<void()> m_callBackFunc;

	bool m_bHover;

	Vector2 GetAbsoluteStartPosition();

public:
	Button();
	~Button();

	void Init(TEXTURE_TYPE _eTextureType, Vector2 _vec2RelativePosition, std::function<void()> _callBackFunc = nullptr);
	void Update() override;
	void Render(HDC _memDC) override;
};

