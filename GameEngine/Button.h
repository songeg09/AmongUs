#pragma once
#include "UIElement.h"

class Texture;
class Button : public UIElement
{
private:
	Vector2 m_vec2Size;
	std::function<void()> m_callBackFunc;
	
public:
	Button();
	~Button();

	void Init(Vector2 _vec2RelativePosition, Vector2 _vec2Size, std::function<void()> _callBackFunc = nullptr);
	void Update() override;
	void Render(HDC _memDC) override;
};

