#pragma once

class UIElement;
class UI abstract
{
protected:
	bool					m_bVisibility;
	std::vector<UIElement*> m_arrUIElemetns;

public:
	UI();
	virtual ~UI();

	virtual void Update();
	virtual void Render(HDC _memDC);
	void SetVisibility(bool _bVisibility) { m_bVisibility = _bVisibility; }
};

