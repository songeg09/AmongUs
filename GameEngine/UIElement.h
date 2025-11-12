#pragma once
class UIElement abstract
{
protected:
	Vector2 m_vec2RelativePosition;

public:
	UIElement();
	~UIElement();

	void Init(Vector2 _vec2RelativePosition);
	virtual void Update() = 0;
	virtual void Render(HDC _memDC) = 0;
};

