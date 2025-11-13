#pragma once

class UIElement;
class UI abstract
{
protected:
	std::vector<UIElement*> m_arrUIElemetns;

public:
	UI();
	virtual ~UI();

	virtual void Init() = 0;
	virtual void Update() final;
	virtual void Render(HDC _memDC);
};

